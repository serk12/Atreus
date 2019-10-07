#include "../header/Shapes.h"

/*--------------------------------------------------*/
/*                  General Purpose                 */
/*--------------------------------------------------*/
sf::Vector2f randomPosition() {
    std::srand(std::time(nullptr));
    sf::Vector2f size = EngineConf::getWindowSize();
    float x           = 50 + std::rand() % (int)(size.x - 100);
    float y           = std::rand() % 400;
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

Circle::Circle(int i) : Circle(200, sf::Vector2f(50, 400))
{
    this->setGravityScale(i);
    this->calcMass(0, true);
}

Circle::Circle(const float r, const sf::Vector2f& pos)
{
    circleShape = sf::CircleShape(r);
    circleShape.setPosition(pos);
    circleShape.setFillColor(sf::Color::Red);

    area = PI * circleShape.getRadius() * circleShape.getRadius();

    this->calcMass(circleShape.getRadius() * circleShape.getRadius());
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circleShape, states);
}

const ShapeRect Circle::getShapeRect() const
{
    float diameter = circleShape.getRadius() * 2;
    return ShapeRect(circleShape.getPosition(), sf::Vector2f(diameter, diameter));
}

void Circle::updateTransform(const sf::Vector2f& pos, const float rotation)
{
    circleShape.setPosition(pos);
    if (!std::isnan(rotation)) circleShape.setRotation(rotation);
}

float Circle::getVolume() const
{
    return area * deep;
}

/*--------------------------------------------------*/
/*                  Rectangle                       */
/*--------------------------------------------------*/

Rectangle::Rectangle() : Rectangle(sf::Vector2f(40, 40), randomPosition())
{}

Rectangle::Rectangle(int i) : Rectangle(sf::Vector2f(400, 20), sf::Vector2f(50, 450))
{
    this->setMaterial(ShapeConf::Static);
    this->setGravityScale(i);
    this->calcMass(0, true);
}

Rectangle::Rectangle(const sf::Vector2f& size, const sf::Vector2f& pos)
{
    rectangleShape = sf::RectangleShape(size);
    rectangleShape.setPosition(pos);
    rectangleShape.setFillColor(sf::Color::White);

    area = rectangleShape.getSize().x * rectangleShape.getSize().y;

    this->calcMass(area);
}

void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rectangleShape, states);
}

const ShapeRect Rectangle::getShapeRect() const
{
    return ShapeRect(rectangleShape.getPosition(), rectangleShape.getSize());
}

void Rectangle::updateTransform(const sf::Vector2f& pos, const float rotation)
{
    rectangleShape.setPosition(pos);
    if (!std::isnan(rotation)) rectangleShape.setRotation(rotation);
}

float Rectangle::getVolume() const
{
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

    this->calcMass(area);
}

void Polygon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(convexShape, states);
}

const ShapeRect Polygon::getShapeRect() const
{
    sf::FloatRect bounds = convexShape.getGlobalBounds();
    return ShapeRect(bounds);
}

void Polygon::updateTransform(const sf::Vector2f& pos, const float rotation)
{
    convexShape.setPosition(pos);
    if (!std::isnan(rotation)) convexShape.setRotation(rotation);
}

float Polygon::getVolume() const
{
    return area * deep;
}
