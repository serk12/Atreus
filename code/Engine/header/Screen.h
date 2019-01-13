
#ifndef SCREEN_HH
#define SCREEN_HH

#include "EngineObject.h"
#include "ControlledActor.h"
#include "Scene.h"

class Screen : public EngineObject {
private:
    ControlledActor controlledActor;
    Scene scene;

public:
    Screen();
    ~Screen();

    void event(sf::Event event) final;
    void update(sf::Time deltatime) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};


#endif // SCREEN_HH
