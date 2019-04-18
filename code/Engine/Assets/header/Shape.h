#ifndef SHAPE_HH
#define SHAPE_HH

#include "Asset.h"
#include "ShapeConf.h"

#include "../../header/EngineConf.h"
#include <random>
#include <iostream>

class Shape : public Asset, public ShapeConf {
private:
    float gravityScale = 40000;
    Material material  = ShapeConf::Rock;
    MassData massData;

    sf::Vector2f velocity = sf::Vector2f(0, 0);

    sf::Vector2f potentialAceleration = sf::Vector2f(0, 0);
    sf::Vector2f externalAceleration  = sf::Vector2f(0, 0);
    static const sf::Vector2f gravityAceleration;

protected:
    void calcMass(bool massInfinite = false);
    void setGravityScale(int scale);

    enum Type { Circle, Rectangle, Polygon };

public:
    Shape();
    void event(sf::Event event) final;
    void update(const float deltatime) final;
    bool canBeRemoved() const final;

    virtual float getVolume()                        = 0;
    virtual void updatePosition(const sf::Vector2f&) = 0;
    // center shape position
    virtual const sf::Vector2f getPosition() const = 0;
    // left bottom corner position
    virtual const sf::FloatRect getPositionAndSizeRect() const = 0;
    virtual Shape::Type getType() const                        = 0;

    static bool broadDetection(const Shape& A, const Shape& B);
    static bool narrowDetection(const Shape& A, const Shape& B);
    static void resolveCollision(Shape& A, Shape& B);
    static const sf::Vector2f calculateNormal(const Shape& A, const Shape& B);
};

#endif // ifndef SHAPE_HH
