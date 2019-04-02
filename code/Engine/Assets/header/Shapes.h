#include "Shape.h"

/*--------------------------------------------------*/
/*                      Circle                      */
/*--------------------------------------------------*/

#ifndef CIRCLE_HH
#define CIRCLE_HH

class Circle : public Shape {
private:
    sf::CircleShape circleShape;
    sf::IntRect boundsRect = sf::IntRect(-1, -1, -1, -1);
    float area             = -1;
    float deep             = 1;

public:
    Circle();
    const sf::IntRect getPossitionAndSizeRect() final;
    void updatePosition(const sf::Vector2f& pos) final;
    float getVolume() final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif // CIRCLE_HH



/*--------------------------------------------------*/
/*                  Rectangle                       */
/*--------------------------------------------------*/

#ifndef RECTANGLE_HH
#define RECTANGLE_HH

#define PI 3.141516

class Rectangle : public Shape {
private:
    sf::RectangleShape rectangleShape;
    sf::IntRect boundsRect = sf::IntRect(-1, -1, -1, -1);
    float area             = -1;
    float deep             = 1;
public:
    Rectangle();
    const sf::IntRect getPossitionAndSizeRect() final;
    void updatePosition(const sf::Vector2f& pos) final;
    float getVolume() final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};
#endif // RECTANGLE_HH



/*--------------------------------------------------*/
/*                  Polygon                         */
/*--------------------------------------------------*/
#ifndef POLYGON_HH
#define POLYGON_HH

class Polygon : public Shape {
private:
    sf::ConvexShape convexShape;
    sf::IntRect boundsRect = sf::IntRect(-1, -1, -1, -1);
    float area             = -1;
    float deep             = 1;

public:
    Polygon();
    const sf::IntRect getPossitionAndSizeRect() final;
    void updatePosition(const sf::Vector2f& pos) final;
    float getVolume() final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif // ifndef POLYGON_HH
