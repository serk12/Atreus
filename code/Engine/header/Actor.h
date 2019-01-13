#ifndef ACTOR_HH
#define ACTOR_HH

#include "EngineObject.h"

class Actor : public EngineObject {
protected:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final
    {
        target.draw(sprite);
    }
};

#endif // ACTOR_HH
