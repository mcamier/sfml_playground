#ifndef TORTUGA_IEVENTHANDLER_HPP
#define TORTUGA_IEVENTHANDLER_HPP


#include <SFML/Window/Event.hpp>

namespace ta {

using sf::Event;

class IEventHandler {
public:
    virtual bool handleEvent(const Event &event) = 0;
};

}

#endif //TORTUGA_IEVENTHANDLER_HPP
