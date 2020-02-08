#include "Shape.h"

/*--------------------------------------------------*/
/*                      Circle                      */
/*--------------------------------------------------*/

#ifndef CIRCLE_HH
#define CIRCLE_HH

class Circle : public Shape {
  private:
    sf::CircleShape circleShape;
    float area;
    float deep = 1;
  public:
    Shape::Type getType() const final {
        return Shape::Type::Circle;
    }

    Circle();
    Circle(int i);
    Circle(const float r, const sf::Vector2f& pos);
    virtual const ShapeRect getShapeRect() const final;
    void updateTransform(const sf::Vector2f& pos, const float rotation) final;
    float getVolume() const final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    const std::vector<sf::Vector2f> getNorm() const final;
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
    float area;
    float deep =  1;
  public:
    Shape::Type getType() const final {
        return Shape::Type::Rectangle;
    }

    Rectangle();
    Rectangle(int i);
    Rectangle(const sf::Vector2f& size, const sf::Vector2f& pos);
    virtual const ShapeRect getShapeRect() const final;
    void updateTransform(const sf::Vector2f& pos, const float rotation) final;
    float getVolume() const final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    const std::vector<sf::Vector2f> getNorm() const final;
};
#endif // RECTANGLE_HH



/*--------------------------------------------------*/
/*                  Polygon                         */
/*--------------------------------------------------*/
#ifndef POLYGON_HH
#define POLYGON_HH

#include <vector>

class Polygon : public Shape {
  private:
    sf::ConvexShape convexShape;
    float area;
    float deep = 1;

  public:
    Shape::Type getType() const final {
        return Shape::Type::Polygon;
    }

    Polygon();
    Polygon(const std::vector<sf::Vector2f>& shape, const sf::Vector2f& pos);
    virtual const ShapeRect getShapeRect() const final;
    void updateTransform(const sf::Vector2f& pos, const float rotation) final;
    float getVolume() const final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    const std::vector<sf::Vector2f> getNorm() const final;
};

#endif // ifndef POLYGON_HH
