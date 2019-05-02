#include "../header/EventManager.h"

using namespace atreus;
std::queue<Event *> EventManager::events;

void EventManager::pushEvent(Event *event)
{
    EventManager::events.push(event);
}

bool EventManager::pollEvent(Event *& event)
{
    if (!EventManager::events.empty()) {
        event = EventManager::events.front();
        EventManager::events.pop();
        return true;
    }
    else {
        return false;
    }
}
