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

// Broad Detection using AABBx to have a cheap and quick solution
// if true and not sqrs => narrowDetection
bool Shape::broadDetection(const Shape& A, const Shape& B)
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

bool Shape::narrowDetection(const Shape& A, const Shape& B)
{
    return true;
}

// http://www.yaldex.com/games-programming/0672323699_ch13lev1sec6.html
// first aproux. best explenation ^
void Shape::resolveCollision(Shape& A, Shape& B)
{
    // Calculate relative velocity
    sf::Vector2f rv = B.velocity - A.velocity;
    // Calculate normal vec, vec that cross the two centers.
    sf::Vector2f n = B.getPosition() - A.getPosition();
    float size     = sqrt(n.x * n.x + n.y * n.y);
    n.x = n.x / size;
    n.y = n.y / size;

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
