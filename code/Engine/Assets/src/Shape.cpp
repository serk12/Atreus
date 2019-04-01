#include "../header/Shape.h"

/*--------------------------------------------------*/
/*                      Shape                       */
/*--------------------------------------------------*/

//  Rock       Density : 0.6  Restitution : 0.1
//  Wood       Density : 0.3  Restitution : 0.2
//  Metal      Density : 1.2  Restitution : 0.05
//  BouncyBall Density : 0.3  Restitution : 0.8
//  SuperBall  Density : 0.3  Restitution : 0.95
//  Pillow     Density : 0.1  Restitution : 0.2
//  Static     Density : 0.0  Restitution : 0.4

void Shape::event(sf::Event event)
{}

void Shape::update(const float deltatime)
{}

// Broad Detection using AABBx to have a cheap and quick solution
bool Shape::broadDetection(const Shape& A, const Shape& B)
{
    // get IntRect and make AAGG vs AABB
}

bool Shape::narrowDetection(const Shape& A, const Shape& B)
{}


/*--------------------------------------------------*/
/*                  General Purpose                 */
/*--------------------------------------------------*/
sf::Vector2f randomPosition() {
    float x = std::rand() % windowWidth;
    float y = std::rand() % windowHeight;
    return sf::Vector2f(x, y);
}


/*--------------------------------------------------*/
/*                      Circle                      */
/*--------------------------------------------------*/
Circle::Circle()
{
    circleShape = sf::CircleShape(40);
    circleShape.setPosition(randomPosition());
    circleShape.setFillColor(sf::Color::Red);
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circleShape, states);
}

const sf::IntRect& Circle::getPossitionAndSizeRect() const
{
    return circleShape.getTextureRect();
}


/*--------------------------------------------------*/
/*                  Rectangle                       */
/*--------------------------------------------------*/
Rectangle::Rectangle()
{
    rectangleShape = sf::RectangleShape(sf::Vector2f(40, 40));
    rectangleShape.setPosition(randomPosition());
    rectangleShape.setFillColor(sf::Color::White);
}

void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rectangleShape, states);
}


const sf::IntRect& Rectangle::getPossitionAndSizeRect() const
{
    return rectangleShape.getTextureRect();
}



/*--------------------------------------------------*/
/*                  Polygon                         */
/*--------------------------------------------------*/
Polygon::Polygon()
{
    convexShape = sf::ConvexShape();
    convexShape.setPointCount(5);
    convexShape.setPoint(0, sf::Vector2f(0, 0));
    convexShape.setPoint(1, sf::Vector2f(0, 10));
    convexShape.setPoint(2, sf::Vector2f(25, 5));
    convexShape.setPoint(3, sf::Vector2f(25, 10));
    convexShape.setPoint(4, sf::Vector2f(25, 0));
    convexShape.setPosition(randomPosition());
    convexShape.setFillColor(sf::Color::White);
}

void Polygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(convexShape, states);
}

const sf::IntRect& Polygon::getPossitionAndSizeRect() const
{
    return convexShape.getTextureRect();
}
