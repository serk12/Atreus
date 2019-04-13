#include "../header/Shape.h"

const sf::Vector2f Shape::gravity = sf::Vector2f(0, 9.81);

Shape::Shape()
{}

void Shape::calcMass()
{
    this->massData.mass    = this->getVolume() * this->material.density;
    this->massData.invMass = 1.0 / this->massData.mass;
}

void Shape::setGravityScale(int scale)
{
    this->gravityScale = scale;
}

void Shape::event(sf::Event event)
{}

void Shape::update(const float dt)
{
    potentialForce = externalForce + gravityScale * Shape::gravity;
    externalForce  = sf::Vector2f(0, 0);

    sf::IntRect  posAndSize = this->getPossitionAndSizeRect();
    sf::Vector2f pos        = sf::Vector2f(posAndSize.left, posAndSize.top);
    float invMass           = this->massData.invMass;

    velocity.x += (invMass * potentialForce.x) * dt;
    pos.x      +=  velocity.x * dt;
    velocity.y += (invMass * potentialForce.y) * dt;
    pos.y      += velocity.y * dt;

    this->updatePosition(pos);
}

// Broad Detection using AABBx to have a cheap and quick solution
// if true and not sqrs => narrowDetection
bool Shape::broadDetection(const Shape& A, const Shape& B)
{
    sf::IntRect aRect = A.getPossitionAndSizeRect();
    sf::IntRect bRect = B.getPossitionAndSizeRect();

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
// first aproux best explenation ^
void Shape::resolveCollision(Shape& A, Shape& B)
{
    // Calculate relative velocity
    sf::Vector2f rv = B.velocity - A.velocity;
    sf::Vector2f n  = B.getPossition() - A.getPossition();

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
