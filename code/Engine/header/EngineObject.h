#ifndef ENGINEOBJECT_HH
#define ENGINEOBJECT_HH

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class EngineObject : public sf::Drawable {
public:
    virtual void event(sf::Event event) {};
    virtual void update(const float deltatime) {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};
};

#endif // ifndef ENGINEOBJECT_HH
