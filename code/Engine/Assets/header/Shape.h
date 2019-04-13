#ifndef SHAPE_HH
#define SHAPE_HH

#include "Asset.h"
#include "ShapeConf.h"

#include "../../header/EngineConf.h"
#include <random>
#include <iostream>

class Shape : public Asset, public ShapeConf {
private:
    float gravityScale = 1000000;
    Material material  = ShapeConf::Rock;
    MassData massData;
    sf::Vector2f velocity = sf::Vector2f(0, 0);

    sf::Vector2f potentialForce = sf::Vector2f(0, 0);
    sf::Vector2f externalForce  = sf::Vector2f(0, 0);
    static const sf::Vector2f gravity;
protected:
    void calcMass();
    void setGravityScale(int scale);

public:
    void event(sf::Event event) final;
    void update(const float deltatime) final;

    virtual const sf::IntRect getPossitionAndSizeRect() const {};
    virtual const sf::Vector2f getPossition() const {};
    virtual float getVolume() {};
    virtual void updatePosition(const sf::Vector2f& pos) {};

    static bool broadDetection(const Shape& A, const Shape& B);
    static bool narrowDetection(const Shape& A, const Shape& B);
    static void resolveCollision(Shape& A, Shape& B);

    Shape();
};

#endif // ifndef SHAPE_HH
