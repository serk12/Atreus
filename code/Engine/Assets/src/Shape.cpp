#include "../header/Shape.h"

const sf::Vector2f Shape::gravity = sf::Vector2f(0, 9.81);

void Shape::event(sf::Event event)
{}

void Shape::update(const float dt)
{
    potentialForce = externalForce + gravityScale * Shape::gravity;
    externalForce  = sf::Vector2f(0, 0);

    sf::IntRect  posAndSize = this->getPossitionAndSizeRect();
    sf::Vector2f pos        = sf::Vector2f(posAndSize.left, posAndSize.top);
    float m                 = this->getVolume() * material.density;

    velocity.x += ((1 / m) * potentialForce.x) * dt;
    pos.x      +=  velocity.x * dt;
    velocity.y += ((1 / m) * potentialForce.y) * dt;
    pos.y      += velocity.y * dt;

    this->updatePosition(pos);
}

// Broad Detection using AABBx to have a cheap and quick solution
bool Shape::broadDetection(const Shape& A, const Shape& B)
{
    // get IntRect and make AAGG vs AABB
}

bool Shape::narrowDetection(const Shape& A, const Shape& B)
{}
