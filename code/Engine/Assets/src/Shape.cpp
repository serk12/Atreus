#include "../header/Shape.h"

const sf::Vector2f Shape::gravityAceleration = sf::Vector2f(0, 9.81);
const float Shape::slop                      = 0.1; // usually 0.01 to 0.1
const float Shape::slopPercent               = 0.4; // usually 20% to 80%

Shape::Shape()
{
    orientation = angularVelocity = torque = 0;
}

bool Shape::canBeRemoved() const
{
    ShapeRect rect   = this->getShapeRect();
    sf::Vector2f min = rect.getMin();
    sf::Vector2f max = rect.getMax();

    sf::Vector2f windowSize = EngineConf::getWindowSize();

    return min.x > windowSize.x || min.y > windowSize.y || max.x < 0 || max.y < 0;
}

void Shape::setMaterial(const Material& shapeConf)
{
    this->material = shapeConf;
}

void Shape::calcMass(float area, bool massInfinite)
{
    if (massInfinite) {
        this->massData.mass = this->massData.invMass = this->massData.inertia = this->massData.inverseInertia = 0;
    }
    else {
        this->massData.mass           = this->getVolume() * this->material.density;
        this->massData.invMass        = 1.0 / this->massData.mass;
        this->massData.inertia        = this->massData.mass * area;
        this->massData.inverseInertia = 1.0 / this->massData.inertia;
    }
}

void Shape::setGravityScale(int scale)
{
    this->gravityScale = scale;
}

void Shape::event(sf::Event&)
{}

void Shape::event(atreus::Event& event)
{
    if (event.type == atreus::Event::EventType::Collision) {
        if (!event.collisionData.done) {
            Shape::positionCorrection(event.collisionData);
            Shape::resolveCollision(*event.collisionData.A, *event.collisionData.B, event.collisionData.n, event.collisionData.contact);

            event.collisionData.done = false;
        }
    }
}

void Shape::update(const float dt)
{
    this->potentialAceleration = this->externalAceleration + gravityScale * Shape::gravityAceleration;
    this->externalAceleration  = sf::Vector2f(0, 0);

    ShapeRect rect   = this->getShapeRect();
    sf::Vector2f pos = rect.getPosition();

    this->velocity += this->potentialAceleration * dt;
    pos.x           = pos.x + velocity.x * dt;
    pos.y           = pos.y + velocity.y * dt;

    angularVelocity += torque * this->massData.inverseInertia * dt;
    // orientation     += angularVelocity * dt;
    this->updateTransform(pos, orientation);
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
    // circle vs circle is True, because is the same as broadDetection
    if ((A.getType() == B.getType()) && (A.getType() == Type::Circle)) return true;

    // SAT:https://gamedevelopment.tutsplus.com/es/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169
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
        ShapeRect aRect   = A.getShapeRect();
        ShapeRect bRect   = B.getShapeRect();
        sf::Vector2f dist = bRect.getCenterPosition() - aRect.getCenterPosition();
        n = bRect.getCenterPosition() - aRect.getCenterPosition();
        float size = sqrt(n.x * n.x + n.y * n.y);
        if (A.getType() == Type::Circle) {
            // Calculate normal vec, vec that cross the two centers.
            penetration = aRect.getRadius() + bRect.getRadius() - size;
            n.x         = n.x / size;
            n.y         = n.y / size;
        }
        else if (A.getType() == Type::Rectangle) {
            sf::Vector2f direction = A.velocity + B.velocity;
            if (direction.x > direction.y) {
                n = ((direction.x > 0) ? sf::Vector2f(1, 0) : sf::Vector2f(-1, 0));
                float a = (aRect.getMax().x - aRect.getMin().x) / 2.0f;
                float b = (bRect.getMax().x - bRect.getMin().x) / 2.0f;

                penetration = a + b - std::abs(dist.x);
            }
            else {
                n = ((direction.y > 0) ? sf::Vector2f(0, 1) : sf::Vector2f(0, -1));
                float a = (aRect.getMax().y - aRect.getMin().y) / 2.0f;
                float b = (bRect.getMax().y - bRect.getMin().y) / 2.0f;

                penetration = a + b - std::abs(dist.y);
            }
        }
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

// https://gamedev.stackexchange.com/questions/105296/calculation-correct-position-of-object-after-collision-2d
void Shape::positionCorrection(atreus::Event::CollisionEvent& collisionData)
{
    sf::Vector2f correction = (std::max(collisionData.penetration - Shape::slop, 0.0f)
                               / (collisionData.A->massData.invMass + collisionData.B->massData.invMass))
                              * Shape::slopPercent *collisionData.n;

    sf::Vector2f posA = collisionData.A->getShapeRect().getPosition();
    posA -= collisionData.A->massData.invMass * correction;
    collisionData.A->updateTransform(posA);

    sf::Vector2f posB = collisionData.B->getShapeRect().getPosition();
    posB += collisionData.B->massData.invMass * correction;
    collisionData.B->updateTransform(posB);
}

// http://www.cs.uu.nl/docs/vakken/mgp/2014-2015/Lecture%207%20-%20Collision%20Resolution.pdf
// first aproux. best explenation ^

void Shape::resolveCollision(Shape& A, Shape& B, sf::Vector2f n, sf::Vector2f)
{
    // COLISION //
    float e              = std::min(A.material.restitution, B.material.restitution);
    sf::Vector2f rv      = B.velocity - A.velocity;
    float velAlongNormal = rv.x * n.x + rv.y * n.y;
    if (velAlongNormal > 0) return;

    float j = (-(1 + e) * velAlongNormal) / (A.massData.invMass + B.massData.invMass);
    if (std::isnan(j)) return;

    A.velocity -= j * A.massData.invMass * n;
    B.velocity += j * B.massData.invMass * n;

    // FRICTION //
    rv             = B.velocity - A.velocity;
    velAlongNormal = rv.x * n.x + rv.y * n.y;

    j = (-(1 + e) * velAlongNormal) / (A.massData.invMass + B.massData.invMass);
    if (std::isnan(j)) return;


    sf::Vector2f t = atreus::Math::tangent(n, rv);
    float jt       = (-rv.x * t.x + rv.y * t.y) / (A.massData.invMass + B.massData.invMass);
    if (std::isnan(jt)) return;

    float mu = sqrt(A.material.staticFriction * A.material.staticFriction +
                    B.material.staticFriction * B.material.staticFriction);
    sf::Vector2f fI;
    if (std::abs(jt) < std::abs(j) * mu) {
        fI = jt * t;
    }
    else {
        fI = -j * t * mu;
    }

    A.velocity += A.massData.invMass * fI;
    B.velocity -= B.massData.invMass * fI;
}
