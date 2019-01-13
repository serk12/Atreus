#ifndef CONTROLLEDACTOR_HH
#define CONTROLLEDACTOR_HH

#include "Actor.h"

class ControlledActor : public Actor {
private:

public:
    ControlledActor();
    ~ControlledActor();

    void event(sf::Event event) final;
    void update(sf::Time deltatime) final;
};

#endif // CONTROLLEDACTOR_HH
