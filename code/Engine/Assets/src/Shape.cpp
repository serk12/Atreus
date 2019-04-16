#include "../header/Shape.h"

const sf::Vector2f Shape::gravityAceleration = sf::Vector2f(0, 9.81);

Shape::Shape()
{}

void Shape::calcMass(bool massInfinite)
{
    if (massInfinite) {
        this->massData.mass    = 0;
        this->massData.invMass = 0;
    }
    else {
        this->massData.mass    = this->getVolume() * this->material.density;
        this->massData.invMass = 1.0 / this->massData.mass;
    }
}

void Shape::setGravityScale(int scale)
{
    this->gravityScale = scale;
}

void Shape::event(sf::Event event)
{}

void Shape::update(const float dt)
{
    this->potentialAceleration = this->externalAceleration + gravityScale * Shape::gravityAceleration;
    this->externalAceleration  = sf::Vector2f(0, 0);

    sf::IntRect  posAndSize = this->getPositionAndSizeRect();
    sf::Vector2f pos        = sf::Vector2f(posAndSize.left, posAndSize.top);
    float invMass           = this->massData.invMass;

    this->velocity.x += (invMass * this->potentialAceleration.x) * dt;
    pos.x            +=  velocity.x * dt;
    this->velocity.y += (invMass * this->potentialAceleration.y) * dt;
    pos.y            += velocity.y * dt;

    this->updatePosition(pos);
}

// Broad Detection using CircleVsCircle to have a cheap and quick solution
// if true => narrowDetection
bool Shape::broadDetection(const Shape& A, const Shape& B)
{
    sf::IntRect aRect = A.getPositionAndSizeRect();
    sf::IntRect bRect = B.getPositionAndSizeRect();

    int aRad = ((aRect.height > aRect.width) ? aRect.height : aRect.width);
    aRad = (aRad + 1) / 2;
    int bRad = ((bRect.height > bRect.width) ? bRect.height : bRect.width);
    bRad = (bRad + 1) / 2;

    int r    = aRad + bRad;
    int left = (aRect.left + aRad) - (bRect.left + bRad);
    int top  = (aRect.top  + aRad) - (bRect.top  + bRad);

    return r * r < (top * top + left * left);
}

bool Shape::narrowDetection(const Shape& A, const Shape& B)
{
    sf::IntRect aRect = A.getPositionAndSizeRect();
    sf::IntRect bRect = B.getPositionAndSizeRect();

    int aMaxX = aRect.left + aRect.width;
    int bMaxX = bRect.left + bRect.width;
    int aMaxY = aRect.top  + aRect.height;
    int bMaxY = bRect.top  + bRect.height;

    int aMinX = aRect.left;
    int bMinX = bRect.left;
    int aMinY = aRect.top;
    int bMinY = bRect.top;

    return !((aMaxY < bMinY) || (aMinY > bMaxY) || (aMaxX < bMinX) || (aMinX > bMaxX));
}

// pre: there is a collision
const sf::Vector2f Shape::calculateNormal(const Shape& A, const Shape& B)
{
    sf::Vector2f n(1, 0);
    if (A.getType() == B.getType()) {
        n = B.getPosition() - A.getPosition();
        if (A.getType() == Type::Circle) {
            // Calculate normal vec, vec that cross the two centers.
            float size = sqrt(n.x * n.x + n.y * n.y);
            n.x = n.x / size;
            n.y = n.y / size;
        }
        else if (A.getType() == Type::Rectangle) {
            sf::Vector2f direction = A.velocity + B.velocity;
            if (direction.x > direction.y) {
                n = ((direction.x > 0) ? sf::Vector2f(1, 0) : sf::Vector2f(-1, 0));
            }
            else {
                n = ((direction.y > 0) ? sf::Vector2f(0, 1) : sf::Vector2f(0, -1));
            }
        }
    }
    else {
        if (((A.getType() == Type::Circle)    && (B.getType() == Type::Rectangle)) ||
            ((A.getType() == Type::Rectangle) && (B.getType() == Type::Circle))) {
            sf::Vector2f circle    = ((A.getType() == Type::Circle) ? A.getPosition() : B.getPosition());
            sf::IntRect  rectan    = ((A.getType() == Type::Rectangle) ? A.getPositionAndSizeRect() : B.getPositionAndSizeRect());
            sf::Vector2f direction = A.velocity + B.velocity;

            if ((direction.x > 0) && (direction.y > 0)) {
                n = circle - sf::Vector2f(rectan.left + rectan.width, rectan.top + rectan.height);
            }
            else if ((direction.x < 0) && (direction.y > 0)) {
                n = circle - sf::Vector2f(rectan.left, rectan.top + rectan.height);
            }
            else if ((direction.x > 0) && (direction.y < 0)) {
                n = circle - sf::Vector2f(rectan.left + rectan.width, rectan.top);
            }
            else {
                n = circle - sf::Vector2f(rectan.left, rectan.top);
            }

            float size = sqrt(n.x * n.x + n.y * n.y);
            n.x = n.x / size;
            n.y = n.y / size;
            if (B.getType() == Type::Rectangle) n = -n;
        }
    }
    return n;
}

// http://www.yaldex.com/games-programming/0672323699_ch13lev1sec6.html
// first aproux. best explenation ^
void Shape::resolveCollision(Shape& A, Shape& B)
{
    // Calculate relative velocity
    sf::Vector2f rv = B.velocity - A.velocity;
    sf::Vector2f n  = Shape::calculateNormal(A, B);
    // Calculate relative velocity in terms of the normal direction
    float velAlongNormal = rv.x * n.x + rv.y * n.y;

    // Do not resolve if velocities are separating
    if (velAlongNormal > 0) return;

    // Calculate restitution
    float e = (A.material.restitution < B.material.restitution) ?
              A.material.restitution : B.material.restitution;

    // Calculate impulse scalar
    float j = -(1 + e) * velAlongNormal;
    j /= A.massData.invMass + B.massData.invMass;

    // Apply impulse
    sf::Vector2f impulse = j * n;
    A.velocity -= A.massData.invMass * impulse;
    B.velocity += B.massData.invMass * impulse;
}
