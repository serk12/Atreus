#ifndef SCENE_HH
#define SCENE_HH

#include "EngineObject.h"

class Scene : public EngineObject {
private:

public:
    Scene();
    ~Scene();

    void event(sf::Event event);
    void update(const float deltatime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // SCENE_HH
