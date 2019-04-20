#include "../header/ShapeRect.h"

ShapeRect::ShapeRect(const sf::Vector2f& pos, const sf::Vector2f& size)
{
    this->pos  = pos;
    this->size = size;
}

ShapeRect::ShapeRect(const sf::FloatRect& rect)
{
    this->pos  = sf::Vector2f(rect.left,  rect.top);
    this->size = sf::Vector2f(rect.width, rect.height);
}

const sf::Vector2f ShapeRect::getCenterPosition() const
{
    float x = this->pos.x + (this->size.x) / 2;
    float y = this->pos.y + (this->size.y) / 2;
    return sf::Vector2f(x, y);
}

const sf::Vector2f ShapeRect::getPosition() const
{
    return pos;
}

const sf::Vector2f ShapeRect::getSize() const
{
    return size;
}

const sf::Vector2f ShapeRect::getMax() const
{
    float x = std::max(this->pos.x + this->size.x, this->pos.x);
    float y = std::max(this->pos.y + this->size.y, this->pos.y);

    return sf::Vector2f(x, y);
}

const sf::Vector2f ShapeRect::getMin() const
{
    float x = std::min(this->pos.x + this->size.x, this->pos.x);
    float y = std::min(this->pos.y + this->size.y, this->pos.y);

    return sf::Vector2f(x, y);
}

const sf::Vector2f ShapeRect::getPosPlusSize() const
{
    float x = this->pos.x + this->size.x;
    float y = this->pos.y + this->size.y;

    return sf::Vector2f(x, y);
}

const float ShapeRect::getRadius() const
{
    float r = std::max(this->size.x, this->size.y) / 2;
    return r;
}
