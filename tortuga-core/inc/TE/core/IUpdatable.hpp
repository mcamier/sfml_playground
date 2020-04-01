#ifndef TORTUGA_IUPDATABLE_HPP
#define TORTUGA_IUPDATABLE_HPP

#include <SFML/System/Time.hpp>

namespace ta {

using sf::Time;

class IUpdatable {
public:
    virtual void update(const Time &) = 0;
};

}

#endif //TORTUGA_IUPDATABLE_HPP
