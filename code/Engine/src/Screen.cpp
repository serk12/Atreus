#include "../header/Screen.h"

Screen::Screen()
{}

Screen::~Screen()
{}

void Screen::event(sf::Event event)
{
    for (std::list<Asset>::iterator it = assets.begin(); it != assets.end(); ++it) {
        it->event(event);
    }
    controlled.event(event);
    scene.event(event);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            assets.push_front(Asset(Asset::Type::Square));
        }
    }
}

void Screen::update(sf::Time deltatime)
{
    for (std::list<Asset>::iterator it = assets.begin(); it != assets.end(); ++it) {
        it->update(deltatime);
    }
    controlled.update(deltatime);
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (std::list<Asset>::const_iterator it = assets.begin(); it != assets.end(); ++it) {
        target.draw(*it);
    }
    target.draw(controlled);
}
