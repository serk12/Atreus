#include "../header/Shape.h"
/*--------------------------------------------------*/
/*                      Circle                      */
/*--------------------------------------------------*/
Circle::Circle()
{
    circleShape = sf::CircleShape(40);
    circleShape.setFillColor(sf::Color::Red);
}

void Circle::event(sf::Event event)
{}

void Circle::update(const float deltatime)
{}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circleShape, states);
}



/*--------------------------------------------------*/
/*                  Rectangle                       */
/*--------------------------------------------------*/
Rectangle::Rectangle()
{
    rectangleShape = sf::RectangleShape(sf::Vector2f(40, 40));
    rectangleShape.setFillColor(sf::Color::White);
}

void Rectangle::event(sf::Event event)
{}

void Rectangle::update(const float deltatime)
{}

void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rectangleShape, states);
}
