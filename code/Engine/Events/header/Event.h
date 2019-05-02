#ifndef EVENT_HH
#define EVENT_HH

#include <SFML/Graphics.hpp>

class Shape;

namespace atreus {
class Event {
  public:
    Event();
    ~Event();

    struct CollisionEvent
    {
        Shape *A;
        Shape *B;
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