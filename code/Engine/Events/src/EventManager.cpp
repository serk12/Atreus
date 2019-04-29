#include "../header/EventManager.h"
namespace atreus {
void EventManager::pushEvent(Event *event)
{
    events.push(event);
}

bool EventManager::pollEvent(Event& event)
{
    if (!events.empty()) {
        event = *(events.front());
        events.pop();
        return true;
    }
    else {
        return false;
    }
}
}
