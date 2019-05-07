#include "../header/Shape.h"

const sf::Vector2f Shape::gravityAceleration = sf::Vector2f(0, 9.81);
const float Shape::slop                      = 0.05;
const float Shape::slopPercent               = 0.2;

Shape::Shape()
{}

bool Shape::canBeRemoved() const
{
    ShapeRect rect   = this->getShapeRect();
    sf::Vector2f min = rect.getMin();
    sf::Vector2f max = rect.getMax();

    sf::Vector2f windowSize = EngineConf::getWindowSize();

    return min.x > windowSize.x || min.y > windowSize.y || max.x < 0 || max.y < 0;
}

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

void Shape::event(sf::Event& event)
{}

void Shape::event(atreus::Event& event)
{
    if (event.type == atreus::Event::EventType::Collision) {
        if (!event.collisionData.done) {
            sf::Vector2f correction = (std::max(event.collisionData.penetration * Shape::slop, 0.0f)
                                       / (event.collisionData.A->massData.invMass + event.collisionData.B->massData.invMass))
                                      * Shape::slopPercent *event.collisionData.n;

            sf::Vector2f posA = event.collisionData.A->getShapeRect().getPosition();
            posA -= event.collisionData.A->massData.invMass * correction;
            event.collisionData.A->updatePosition(posA);

            sf::Vector2f posB = event.collisionData.B->getShapeRect().getPosition();
            posB += event.collisionData.B->massData.invMass * correction;
            event.collisionData.B->updatePosition(posB);
            event.collisionData.done = !event.collisionData.done;
        }
    }
}

void Shape::update(const float dt)
{
    this->potentialAceleration = this->externalAceleration + gravityScale * Shape::gravityAceleration;
    this->externalAceleration  = sf::Vector2f(0, 0);

    ShapeRect rect   = this->getShapeRect();
    sf::Vector2f pos = rect.getPosition();
    float invMass    = this->massData.invMass;

    this->velocity.x += (invMass * this->potentialAceleration.x) * dt;
    pos.x             = pos.x + velocity.x * dt;

    this->velocity.y += (invMass * this->potentialAceleration.y) * dt;
    pos.y             = pos.y + velocity.y * dt;
    // descomposet works faster^
    this->updatePosition(pos);
}

inline float clamp(float x, float  min, float  max)
{
    return (x < min) ? min : ((x > max) ? max : x);
}

sf::Vector2f Shape::minDistanceSquareCircle(const Shape& A, const Shape& B)
{
    ShapeRect shape  = (A.getType() == Type::Circle) ? B.getShapeRect() : A.getShapeRect();
    ShapeRect circle = (A.getType() == Type::Circle) ? A.getShapeRect() : B.getShapeRect();

    sf::Vector2f circleCenter = circle.getCenterPosition();

    sf::Vector2f clampCircleInShape(clamp(circleCenter.x, shape.getPosition().x, shape.getPosPlusSize().x),
                                    clamp(circleCenter.y, shape.getPosition().y, shape.getPosPlusSize().y));

    return circleCenter - clampCircleInShape;
}

// Broad Detection using CircleVsCircle to have a cheap and quick solution
// if true => narrowDetection
bool Shape::broadDetection(const Shape& A, const Shape& B)
{
    ShapeRect aRect = A.getShapeRect();
    ShapeRect bRect = B.getShapeRect();

    sf::Vector2f bPos = bRect.getCenterPosition();
    sf::Vector2f aPos = aRect.getCenterPosition();
    float top         = aPos.y - bPos.y;
    float left        = aPos.x - bPos.x;

    float r = bRect.getRadius() + aRect.getRadius();

    return r * r > (top * top + left * left);
}

bool Shape::narrowDetection(const Shape& A, const Shape& B)
{
    if ((A.getType() == B.getType()) && (A.getType() == Type::Circle)) return true;

    if ((A.getType() == B.getType()) && (A.getType() == Type::Rectangle)) {
        ShapeRect aRect = A.getShapeRect();
        ShapeRect bRect = B.getShapeRect();

        sf::Vector2f aMin = aRect.getPosition();
        sf::Vector2f bMin = bRect.getPosition();

        sf::Vector2f aMax = aRect.getPosPlusSize();
        sf::Vector2f bMax = bRect.getPosPlusSize();

        // Amax > Bmin && Amin < Bmin
        return !((aMax.y < bMin.y) || (aMin.y > bMax.y) ||
                 (aMax.x < bMin.x) || (aMin.x > bMax.x));
    }
    else if (((A.getType() == Type::Circle)    && (B.getType() == Type::Rectangle)) ||
             ((A.getType() == Type::Rectangle) && (B.getType() == Type::Circle))) {
        sf::Vector2f dis = Shape::minDistanceSquareCircle(A, B);
        float r          = (A.getType() == Type::Circle) ? A.getShapeRect().getRadius() : B.getShapeRect().getRadius();
        return dis.x * dis.x + dis.y * dis.y < r * r;
    }
    return false;
}

// pre: there is a collision
const sf::Vector2f Shape::calculateNormal(const Shape& A, const Shape& B, float& penetration)
{
    sf::Vector2f n(0, 0);
    penetration = -1;
    if (A.getType() == B.getType()) {
        ShapeRect aRect = A.getShapeRect();
        ShapeRect bRect = B.getShapeRect();
        n = bRect.getCenterPosition() - aRect.getCenterPosition();
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
        float aExtendedY = (aRect.getPosition().y - aRect.getPosPlusSize().y) / 2;
        float bExtendedY = (bRect.getPosition().y - bRect.getPosPlusSize().y) / 2;
        float yOverlap   = aExtendedY + bExtendedY - std::abs(n.y);
        float aExtendedX = (aRect.getPosition().x - aRect.getPosPlusSize().x) / 2;
        float bExtendedX = (bRect.getPosition().x - bRect.getPosPlusSize().x) / 2;
        float xOverlap   = aExtendedX + bExtendedX - std::abs(n.x);
        penetration = std::max(xOverlap, yOverlap);
    }
    else {
        if (((A.getType() == Type::Circle)    && (B.getType() == Type::Rectangle)) ||
            ((A.getType() == Type::Rectangle) && (B.getType() == Type::Circle))) {
            n = Shape::minDistanceSquareCircle(A, B);
            float size = sqrt(n.x * n.x + n.y * n.y);
            n.x = n.x / size;
            n.y = n.y / size;
            if (B.getType() == Type::Rectangle) n = -n;
            float r = (A.getType() == Type::Circle) ? A.getShapeRect().getRadius() : B.getShapeRect().getRadius();
            penetration = size - r;
        }
    }
    penetration = std::abs(penetration);
    return n;
}

// http://www.yaldex.com/games-programming/0672323699_ch13lev1sec6.html
// first aproux. best explenation ^
void Shape::resolveCollision(Shape& A, Shape& B, sf::Vector2f n)
{
    // Calculate relative velocity
    sf::Vector2f rv = B.velocity - A.velocity;
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
