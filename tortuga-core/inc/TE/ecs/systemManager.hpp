#ifndef TORTUGA_SYSTEM_MANAGER_HPP
#define TORTUGA_SYSTEM_MANAGER_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <set>
#include <string>
#include "../core/IUpdatable.hpp"
#include "../ecs/base.hpp"
#include "../logger.hpp"
#include "component.hpp"
#include "system.hpp"

namespace ta {

using namespace utils;

using std::list;
using std::string;

//
//
class SystemManager : public IUpdatable {
    friend class EntityManager;

    list<ISystem*> systems;

private:
    void notifyEntityUpdate(EntityId id, ComponentBitMask componentBitMask);

public:
    void addSystem(ISystem* system);

    void update(const Time&) override;

};

}

#endif //TORTUGA_SYSTEM_HPP
