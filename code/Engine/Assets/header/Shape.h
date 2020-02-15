#ifndef SHAPE_HH
#define SHAPE_HH

#include "Asset.h"
#include "ShapeConf.h"

#include "../../header/EngineConf.h"
#include "ShapeRect.h"
#include "../../../math.h"
#include <random>

class Shape : public Asset, public ShapeConf {
  private:
    float gravityScale = 100;
    Material material  = ShapeConf::BouncyBall;
    MassData massData;
    float orientation = 0, angularVelocity = 0, torque = 0;

    sf::Vector2f velocity            = sf::Vector2f(0, 0),
                 externalVelocity    = sf::Vector2f(0, 0),
                 externalAceleration = sf::Vector2f(0, 0);

    static const sf::Vector2f gravityAceleration;
    static const float slop;
    static const float slopPercent;
    // min distance between the closest corner and the circle center
    // Pre: A or B has to be a circle
    // Post: Circle - Shape
    static sf::Vector2f minDistanceSquareCircle(const Shape& A, const Shape& B);
    static void positionCorrection(atreus::Event::CollisionEvent& collisionData);

  protected:
    void setMaterial(const Material& shapeConf);
    void calcMass(float radius, bool massInfinite = false);
    void setGravityScale(int scale);

    enum Type { Circle, Rectangle, Polygon };

  public:
    Shape();
    void event(sf::Event& event) final;
    void event(atreus::Event& event) final;
    void update(const float deltatime) final;
    bool canBeRemoved() const final;

    virtual float getVolume() const                               = 0;
    virtual void updateTransform(const sf::Vector2f&, const float = NAN) = 0;
    virtual const ShapeRect getShapeRect() const                  = 0;
    // Return the normals in localSpace
    virtual const std::vector<sf::Vector2f> getNorm() const = 0;
    virtual Shape::Type getType() const = 0;

    static bool broadDetection(const Shape& A, const Shape& B);
    static bool narrowDetection(const Shape& A, const Shape& B);
    static void resolveCollision(Shape& A, Shape& B, sf::Vector2f n, sf::Vector2f contact);
    static const sf::Vector2f calculateNormal(const Shape& A, const Shape& B, float& penetration);
};

#endif // ifndef SHAPE_HH
