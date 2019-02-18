#ifndef ASSET_HH
#define ASSET_HH

#include "EngineObject.h"
#include "../../utils.h"

class Asset : public EngineObject {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    bool drawable = false;
public:

    enum Type { Square, Circle, Poligon };
    Asset();
    Asset(Type type);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    const sf::IntRect& getIntRect() const;
};

#endif // ASSET_HH
