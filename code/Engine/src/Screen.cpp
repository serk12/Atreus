#include "../header/Screen.h"

Screen::Screen()
{}

Screen::~Screen()
{}

void Screen::event(sf::Event event)
{
    for (std::list<Actor>::iterator it = actors.begin(); it != actors.end(); ++it) {
        it->event(event);
    }
    controlled.event(event);
    scene.event(event);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            actors.push_front(Actor(Actor::Type::Square));
        }
    }
}

void Screen::update(sf::Time deltatime)
{
    for (std::list<Actor>::iterator it = actors.begin(); it != actors.end(); ++it) {
        it->update(deltatime);
    }
    controlled.update(deltatime);
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (std::list<Actor>::const_iterator it = actors.begin(); it != actors.end(); ++it) {
        target.draw(*it);
    }
    target.draw(controlled);
}
