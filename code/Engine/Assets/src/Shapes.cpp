#include "../header/Shapes.h"

/*--------------------------------------------------*/
/*                  General Purpose                 */
/*--------------------------------------------------*/
sf::Vector2f randomPosition() {
    sf::Vector2f size = EngineConf::getWindowSize();
    float x           = std::rand() % (int)size.x;
    float y           = std::rand() % (int)size.y;
    return sf::Vector2f(x, y);
}

float getDistance(const sf::Vector2f& A, const sf::Vector2f& B)
{
    float x = A.x - B.x;
    float y = A.y - B.y;

    return sqrt(x * x + y * y);
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

const sf::IntRect Circle::getPossitionAndSizeRect()
{
    if (boundsRect.left == -1) {
        boundsRect.left   = circleShape.getPosition().x;
        boundsRect.top    = circleShape.getPosition().y;
        boundsRect.width  = circleShape.getRadius() * 2;
        boundsRect.height = circleShape.getRadius() * 2;
    }
    return boundsRect;
}

void Circle::updatePosition(const sf::Vector2f& pos)
{
    circleShape.setPosition(pos);
}

float Circle::getVolume()
{
    if (area == -1) {
        area = PI * circleShape.getRadius() * circleShape.getRadius();
    }
    return area * deep;
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


const sf::IntRect Rectangle::getPossitionAndSizeRect()
{
    if (boundsRect.left == -1) {
        boundsRect.left   = rectangleShape.getPosition().x;
        boundsRect.top    = rectangleShape.getPosition().y;
        boundsRect.width  = rectangleShape.getSize().x;
        boundsRect.height = rectangleShape.getSize().y;
    }
    return boundsRect;
}

void Rectangle::updatePosition(const sf::Vector2f& pos)
{
    rectangleShape.setPosition(pos);
}

float Rectangle::getVolume()
{
    if (area == -1) {
        area = rectangleShape.getSize().x * rectangleShape.getSize().y;
    }
    return area * deep;
}


/*--------------------------------------------------*/
/*                  Polygon                         */
/*--------------------------------------------------*/
Polygon::Polygon()
{
    convexShape = sf::ConvexShape();
    convexShape.setPointCount(5);
    convexShape.setPoint(0, sf::Vector2f(0, 0));
    convexShape.setPoint(1, sf::Vector2f(0, 30));
    convexShape.setPoint(2, sf::Vector2f(30, 60));
    convexShape.setPoint(3, sf::Vector2f(30, 30));
    convexShape.setPoint(4, sf::Vector2f(0, 60));
    convexShape.setPosition(randomPosition());
    convexShape.setFillColor(sf::Color::White);
}

void Polygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(convexShape, states);
}

const sf::IntRect Polygon::getPossitionAndSizeRect()
{
    if (boundsRect.left == -1) {
        sf::FloatRect bounds = convexShape.getGlobalBounds();
        boundsRect.left   = bounds.left;
        boundsRect.top    = bounds.top;
        boundsRect.width  = bounds.width;
        boundsRect.height = bounds.height;
    }
    return boundsRect;
}

void Polygon::updatePosition(const sf::Vector2f& pos)
{
    convexShape.setPosition(pos);
}

float Polygon::getVolume()
{
    if (area == -1) {
        area = 0;
        int count = convexShape.getPointCount();
        for (int i = 0; i < count; ++i) { // aprox
            float a = getDistance(convexShape.getPoint(i),               convexShape.getPoint((i + 1) % count));
            float b = getDistance(convexShape.getPoint((i + 1) % count), convexShape.getPoint((i + 2) % count));
            float c = getDistance(convexShape.getPoint((i + 2) % count), convexShape.getPoint(i));

            // Heron's Formula
            float p = (a + b + c) / 2;
            area += sqrt(p * (p - a) * (p - b) * (p - c));
        }
    }
    return area * deep;
}
