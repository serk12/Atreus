#include "../header/Asset.h"

Asset::Asset()
{}

Asset::Asset(Type type) {
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


void Asset::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (drawable) {
        target.draw(sprite);
    }
}

const sf::IntRect& Asset::getIntRect() const
{
    return this.Sprite.getTextureRect();
}
