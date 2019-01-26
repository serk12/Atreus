#ifndef ACTOR_HH
#define ACTOR_HH

#include "EngineObject.h"
#include "../../utils.h"

class Actor : public EngineObject {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    bool drawable = false;
public:

    enum Type { Square, Circle, Poligon };
    Actor() {}
    Actor(Type type) {
        switch (type) {
        case Type::Square:
        default:
            if (!this->texture.loadFromFile("data/square.png")) return;

            this->sprite = sf::Sprite(this->texture);
            this->sprite.setPosition(sf::Mouse::getPosition().x - windowCoordx, sf::Mouse::getPosition().y - windowCoordy);
            this->sprite.setScale(0.01f, 0.01f);
            this->drawable = true;
            break;
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const final
    {
        if (drawable) {
            target.draw(sprite);
        }
    }
};

#endif // ACTOR_HH
