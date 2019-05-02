#ifndef ENGINEOBJECT_HH
#define ENGINEOBJECT_HH

#include <SFML/Graphics.hpp>
#include "Events/header/EventManager.h"
#include "Events/header/Event.h"

class EngineObject {
  public:
    virtual void event(sf::Event& event) = 0;
    virtual void event(atreus::Event& event) = 0;
    virtual void update(const float deltatime) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

#endif // ifndef ENGINEOBJECT_HH
