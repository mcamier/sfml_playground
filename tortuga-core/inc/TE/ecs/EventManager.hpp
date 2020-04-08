#ifndef TORTUGA_EVENTMANAGER_HPP
#define TORTUGA_EVENTMANAGER_HPP

#include "../message/message.hpp"

#include <map>
#include <list>

namespace ta {

using namespace std;

class EventManager {
private:
    //map<messageType, map<EntityId, list<Observer*>>> observers;

public:
    EventManager();

    EventManager(const EventManager&) = delete;

    EventManager& operator=(const EventManager&) = delete;

    EventManager(EventManager&& other) = default;

    EventManager& operator=(EventManager&& other) = default;

    ~EventManager();
};

}

#endif //TORTUGA_EVENTMANAGER_HPP