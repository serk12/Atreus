#include "../header/Screen.h"

Screen::Screen()
{}
Screen::~Screen()
{}

void Screen::event(sf::Event event)
{
    controlledActor.event(event);
}

void Screen::update(sf::Time deltatime)
{}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{}
