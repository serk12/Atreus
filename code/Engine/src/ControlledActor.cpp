#include "../header/ControlledActor.h"

ControlledActor::ControlledActor()
{}

ControlledActor::~ControlledActor() {}

void ControlledActor::event(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (!this->texture.loadFromFile("data/square.png")) return;

            this->sprite = sf::Sprite(this->texture);
            this->sprite.setPosition(sf::Mouse::getPosition().x - windowCoordx, sf::Mouse::getPosition().y - windowCoordy);
            // this->sprite.setScale(0.001f, 0.001f);
            this->drawable = true;
        }
    }
}

void ControlledActor::update(sf::Time deltatime)
{}
