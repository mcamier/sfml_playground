#ifndef TORTUGA_SYSTEM_MANAGER_HPP
#define TORTUGA_SYSTEM_MANAGER_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <set>
#include <string>
#include "../core/IUpdatable.hpp"
#include "../ecs/base.hpp"
#include "../logger.hpp"
#include "component.hpp"

namespace ta {

using namespace utils;

using std::list;
using std::string;


class ISystem;
class EntityManager;

//
//
class SystemManager : public IUpdatable {
    friend class EntityManager;
    friend class ISystem;

private:
    EntityManager* entityManager;
    list<ISystem*> systems;

    void notifyEntityUpdate(EntityId id, ComponentBitMask componentBitMask);

public:
    void addSystem(ISystem* system);

    void update(const Time&) override;

    void handleEvent();

};

}

#endif
