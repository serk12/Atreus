#ifndef CIRCLE_HH
#define CIRCLE_HH

#include "Asset.h"
#include "../../../debug.h"

class Circle : public Asset {
private:
    sf::CircleShape circleShape;

public:
    Circle();
    void event(sf::Event event) final;
    void update(const float deltatime) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif // CIRCLE_HH




#ifndef RECTANGLE_HH
#define RECTANGLE_HH

#include "Asset.h"

class Rectangle : public Asset {
private:
    sf::RectangleShape rectangleShape;

public:
    Rectangle();
    void event(sf::Event event) final;
    void update(const float deltatime) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};
#endif // RECTANGLE_HH
