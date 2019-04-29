#ifndef EVENT_HH
#define EVENT_HH

#include <SFML/Graphics.hpp>

namespace atreus {
class Event {
  public:
    struct CollisionEvent
    {
        float        penetration;
        float        totalInerseMass;
        sf::Vector2f n;
    };

    enum EventType
    {
        Collision
    };


    // member data
    EventType type;

    union
    {
        CollisionEvent collisionData;
    };
};
}

#endif // ifndef EVENT_HH
