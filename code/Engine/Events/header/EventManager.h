#ifndef EVENTMANAGER_HH
#define EVENTMANAGER_HH

#include <queue>
#include "Event.h"
namespace atreus {
class EventManager {
  private:
    std::queue<Event *> events;
  public:
    void pushEvent(Event *event);
    bool pollEvent(Event& event);
    // bool waitEvent(const Event& event); //for now there is no need
};
}
#endif // ifndef EVENTMANAGER_HH
