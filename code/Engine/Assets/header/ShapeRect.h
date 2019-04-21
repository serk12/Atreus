#ifndef SHAPERECT_HH
#define SHAPERECT_HH

#include <SFML/Graphics.hpp>

class ShapeRect {
private:
    sf::Vector2f pos;
    sf::Vector2f size;

public:
    ShapeRect(const sf::Vector2f& pos, const sf::Vector2f& size);
    ShapeRect(const sf::FloatRect& rect);

    const sf::Vector2f getCenterPosition() const;
    const sf::Vector2f getPosPlusSize() const;
    const sf::Vector2f getPosition() const;
    const sf::Vector2f getSize() const;
    const sf::Vector2f getMax() const;
    const sf::Vector2f getMin() const;
    float getRadius() const;
};

#endif // ifndef SHAPERECT_HH
