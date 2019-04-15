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
Circle::Circle() : Circle(40, randomPosition())
{}


Circle::Circle(const float r, const sf::Vector2f& pos)
{
    circleShape = sf::CircleShape(r);
    circleShape.setPosition(pos);
    circleShape.setFillColor(sf::Color::Red);

    this->calcMass();
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circleShape, states);
}

const sf::IntRect Circle::getPositionAndSizeRect() const
{
    sf::IntRect boundsRect = sf::IntRect(-1, -1, -1, -1);

    boundsRect.left   = circleShape.getPosition().x;
    boundsRect.top    = circleShape.getPosition().y;
    boundsRect.width  = circleShape.getRadius() * 2;
    boundsRect.height = circleShape.getRadius() * 2;

    return boundsRect;
}

const sf::Vector2f Circle::getPosition() const
{
    return sf::Vector2f(circleShape.getPosition().x + circleShape.getRadius(),
                        circleShape.getPosition().y + circleShape.getRadius());
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

Rectangle::Rectangle() : Rectangle(sf::Vector2f(40, 40), randomPosition())
{}

Rectangle::Rectangle(int i) : Rectangle(sf::Vector2f(400, 20), sf::Vector2f(50, 450))
{
    this->setGravityScale(i);
}

Rectangle::Rectangle(const sf::Vector2f& size, const sf::Vector2f& pos)
{
    rectangleShape = sf::RectangleShape(size);
    rectangleShape.setPosition(pos);
    rectangleShape.setFillColor(sf::Color::White);

    this->calcMass();
}

void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rectangleShape, states);
}


const sf::IntRect Rectangle::getPositionAndSizeRect() const
{
    sf::IntRect boundsRect = sf::IntRect(-1, -1, -1, -1);

    boundsRect.left   = rectangleShape.getPosition().x;
    boundsRect.top    = rectangleShape.getPosition().y;
    boundsRect.width  = rectangleShape.getSize().x;
    boundsRect.height = rectangleShape.getSize().y;

    return boundsRect;
}

const sf::Vector2f Rectangle::getPosition() const
{
    return sf::Vector2f(rectangleShape.getPosition().x + rectangleShape.getSize().x / 2,
                        rectangleShape.getPosition().y + rectangleShape.getSize().y / 2);
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
Polygon::Polygon() : Polygon({
    sf::Vector2f(0, 0),    sf::Vector2f(0, 30),    sf::Vector2f(30, 60),    sf::Vector2f(60, 30), sf::Vector2f(0, 30)
}, randomPosition())
{}

Polygon::Polygon(const std::vector<sf::Vector2f>& shape, const sf::Vector2f& pos)
{
    convexShape = sf::ConvexShape();
    convexShape.setPointCount(shape.size());
    for (unsigned int i = 0; i < shape.size(); ++i) {
        convexShape.setPoint(i, shape[i]);
    }
    convexShape.setPosition(pos);
    convexShape.setFillColor(sf::Color::White);

    this->calcMass();
}

void Polygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(convexShape, states);
}

const sf::IntRect Polygon::getPositionAndSizeRect() const
{
    sf::IntRect boundsRect = sf::IntRect(-1, -1, -1, -1);

    sf::FloatRect bounds = convexShape.getGlobalBounds();
    boundsRect.left   = bounds.left;
    boundsRect.top    = bounds.top;
    boundsRect.width  = bounds.width;
    boundsRect.height = bounds.height;

    return boundsRect;
}

const sf::Vector2f Polygon::getPosition() const
{
    sf::IntRect boundsRect = this->getPositionAndSizeRect();
    return sf::Vector2f(boundsRect.left + boundsRect.width / 2,
                        boundsRect.top + boundsRect.height / 2);
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
        // Green's theorem
        // clockwise => negative area
        // holes and slef-crossing => 0
        for (int i = 0; i < count; ++i) {
            int j = (i + 1) % count;
            area += convexShape.getPoint(i).x * convexShape.getPoint(j).y;
            area -= convexShape.getPoint(i).y * convexShape.getPoint(j).x;
        }
        area = -area * 0.5;
    }
    return area * deep;
}
