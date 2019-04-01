#include "../header/Screen.h"

Screen::Screen()
{}

Screen::~Screen()
{}

void Screen::event(sf::Event event)
{
    for (std::list<Asset *>::iterator itAsset = assets.begin(); itAsset != assets.end(); ++itAsset) {
        (*itAsset)->event(event);
    }
    scene.event(event);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            assets.push_front(new Rectangle());
        }
        else if (event.mouseButton.button == sf::Mouse::Middle) {
            assets.push_front(new Circle());
        }
        else if (event.mouseButton.button == sf::Mouse::Right) {
            assets.push_front(new Polygon());
        }
    }
}

void Screen::update(const float deltatime)
{
    for (std::list<Asset *>::iterator itAsset = assets.begin(); itAsset != assets.end(); ++itAsset) {
        (*itAsset)->update(deltatime);
    }
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (std::list<Asset *>::const_iterator itAsset = assets.begin(); itAsset != assets.end(); ++itAsset) {
        (*itAsset)->draw(target, states);
    }
}
