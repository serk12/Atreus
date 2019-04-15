#ifndef SCENE_HH
#define SCENE_HH

#include "EngineObject.h"

class Scene : public EngineObject {
private:

public:
    Scene();
    ~Scene();

    void event(sf::Event event) final;
    void update(const float deltatime) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif // SCENE_HH
