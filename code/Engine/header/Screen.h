
#ifndef SCREEN_HH
#define SCREEN_HH

#include <list>

#include "EngineObject.h"
#include "Scene.h"
#include "Asset.h"

class Screen : public EngineObject {
private:
    std::list<Asset> assets;
    Scene scene;

public:
    Screen();
    ~Screen();

    void event(sf::Event event) final;
    void update(const float deltatime) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};


#endif // SCREEN_HH
