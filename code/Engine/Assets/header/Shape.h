
/*--------------------------------------------------*/
/*                      Shape                       */
/*--------------------------------------------------*/

#ifndef SHAPE_HH
#define SHAPE_HH

#include "Asset.h"

struct MassData
{
    float mass, inv_mass;
    float inertia, inverse_inertia;
};

struct Material
{
    float density, restitution;
};

class Shape : public Asset {
private:
    float gravityScale;
    Material material;
    MassData mass_data;
    sf::Vector2f velocity;
    sf::Vector2f force;

public:
    void event(sf::Event event) final;
    void update(const float deltatime) final;

    virtual sf::IntRect& getPossitionAndSizeRect() const;

    static bool broadDetection(const Shape& A, const Shape& B);
    static bool narrowDetection(const Shape& A, const Shape& B);
};

#endif // ifndef SHAPE_HH



/*--------------------------------------------------*/
/*                      Circle                      */
/*--------------------------------------------------*/

#ifndef CIRCLE_HH
#define CIRCLE_HH

class Circle : public Shape {
private:
    sf::CircleShape circleShape;

public:
    Circle();
    sf::IntRect& getPossitionAndSizeRect() const final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif // CIRCLE_HH



/*--------------------------------------------------*/
/*                  Rectangle                       */
/*--------------------------------------------------*/

#ifndef RECTANGLE_HH
#define RECTANGLE_HH

class Rectangle : public Shape {
private:
    sf::RectangleShape rectangleShape;

public:
    Rectangle();
    sf::IntRect& getPossitionAndSizeRect() const final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};
#endif // RECTANGLE_HH



/*--------------------------------------------------*/
/*                  Polygon                         */
/*--------------------------------------------------*/
#ifndef POLYGON_HH
#defnie POLYGON_HH

class Polygon : public Shape {
private:
    sf::ConvexShape convexShape;

public:
    Polygon();
    sf::IntRect& getPossitionAndSizeRect() const final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif // ifndef POLYGON_HH
