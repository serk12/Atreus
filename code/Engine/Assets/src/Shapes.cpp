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

inline std::vector<sf::Vector2f> calcNorm(const sf::Shape& shape) {
    int points = shape.getPointCount();
    std::vector<sf::Vector2f> norm(points);
    sf::Vector2f pointA = shape.getPoint(points - 1) + shape.getPosition();
    pointA.x *= shape.getScale().x;
    pointA.y *= shape.getScale().y;
    for (int i = 0; i < points; ++i) {
        // ToDo: rotation
        sf::Vector2f pointB = (shape.getPoint(i) + shape.getPosition());
        pointB.x *= shape.getScale().x;
        pointB.y *= shape.getScale().y;
        sf::Vector2f lineI = pointA - pointB;
        pointA = pointB;
        sf::Vector2f normalI = sf::Vector2f(lineI.y, -1 * lineI.x);
        norm[i] = normalI;
    }
    return norm;
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

    area = atreus::Math::PI *circleShape.getRadius() * circleShape.getRadius();

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

const std::vector<sf::Vector2f> Circle::getNorm() const
{
    std::vector<sf::Vector2f> none(0);
    return none;
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
    convexShape.setPointCount(4);
    convexShape.setPoint(0, sf::Vector2f(0, 0));
    convexShape.setPoint(1, sf::Vector2f(0, size.y));
    convexShape.setPoint(2, sf::Vector2f(size.x, size.y));
    convexShape.setPoint(3, sf::Vector2f(size.x, 0));
    convexShape.setPosition(pos);
    convexShape.setFillColor(sf::Color::White);

    area = size.x * size.y;

    this->calcMass(area);
}

/*--------------------------------------------------*/
/*                  Polygon                         */
/*--------------------------------------------------*/

std::vector<sf::Vector2f> randomConvexPolygon()
{
    std::vector<sf::Vector2f> result;
    int r = 40 + std::rand() % 60;
    int angle = 0, top = 180;
    for (int i = 0; i < 3; ++i) {
        result.push_back(sf::Vector2f(r + cos(atreus::Math::degreeToRad(angle)) * r,
                                      r + sin(atreus::Math::degreeToRad(angle)) * r));
        int v = angle  + std::rand() % (angle + top);
        while (v < (angle + top - 20)) {
            result.push_back(sf::Vector2f(r + cos(atreus::Math::degreeToRad(v)) * r,
                                          r + sin(atreus::Math::degreeToRad(v)) * r));
            v = v + std::rand() % ((angle + top) - v);
        }
        if (i == 0) { angle = 180; top = 90; }
        if (i == 1) { angle = 270; top = 90; }
    }

    return result;
}

Polygon::Polygon() : Polygon(randomConvexPolygon(), randomPosition())
{}

Polygon::Polygon(const std::vector<sf::Vector2f>& shape, const sf::Vector2f& pos)
{
    convexShape = sf::ConvexShape();
    convexShape.setPointCount(shape.size());
    for (unsigned int i = 0; i < shape.size(); ++i) {
        convexShape.setPoint(i, shape[i]);
    }
    convexShape.setPosition(pos);
    convexShape.setFillColor(sf::Color::Blue);

    area = 0;
    int count = convexShape.getPointCount();
    // Green's theorem
    // clockwise => negative area
    // holes and self-crossing => 0
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

const std::vector<sf::Vector2f> Polygon::getNorm() const
{
    return calcNorm(convexShape);
}
