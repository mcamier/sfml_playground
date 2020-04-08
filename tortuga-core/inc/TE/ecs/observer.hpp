#ifndef TORTUGA_OBSERVER_HPP
#define TORTUGA_OBSERVER_HPP

#include "../ecs/base.hpp"

namespace ta {

struct message;

class Observer {

public:
    virtual void notify(EntityId id, const message& message);

};

}

#endif //TORTUGA_OBSERVER_HPP