#include "../header/Screen.h"

Screen::Screen()
{
    actors.push_front(ControlledActor());
    actors.begin()->event(sf::Event());
}
Screen::~Screen()
{}

void Screen::event(sf::Event event)
{
    for (std::list<ControlledActor>::iterator it = actors.begin(); it != actors.end(); ++it) {
        it->event(event);
    }
    scene.event(event);
}

void Screen::update(sf::Time deltatime)
{
    for (std::list<ControlledActor>::iterator it = actors.begin(); it != actors.end(); ++it) {
        it->update(deltatime);
    }
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (std::list<ControlledActor>::const_iterator it = actors.begin(); it != actors.end(); ++it) {
        target.draw(*it);
    }
}
