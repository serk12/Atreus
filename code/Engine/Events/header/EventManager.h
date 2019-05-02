#ifndef EVENTMANAGER_HH
#define EVENTMANAGER_HH

#include <iostream>

#include <queue>
#include "Event.h"

namespace atreus {
class Event;

class EventManager {
  private:
    static std::queue<Event *> events;
  public:
    static void pushEvent(Event *event);
    static bool pollEvent(Event *& event);
    // bool waitEvent(const Event& event); //for now there is no need
};
}
#endif // ifndef EVENTMANAGER_HH
