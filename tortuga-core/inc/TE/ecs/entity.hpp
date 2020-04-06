#ifndef TORTUGA_ENTITY_HPP
#define TORTUGA_ENTITY_HPP

#include <map>
#include <list>

#include "component.hpp"
#include "systemManager.hpp"
#include "base.hpp"


namespace ta {

using std::map;
using std::list;

class EntityManager {

private:
    SystemManager* systemManager;
    EntityId lastEntityId = 0;
    map<EntityId, list<IComponent*>> entityComponents;

public:
    EntityManager(SystemManager* systemManager) : systemManager(systemManager) {}

    EntityId addEntity();
    void removeEntity(EntityId id);
    void addComponent(EntityId id, IComponent* component);

    template<typename COMP>
    void removeComponent(EntityId id) {
        auto it = entityComponents.find(id);
        if(it != entityComponents.end()) {
            auto& components = (*it).second;
            bool deleted = false;
            for (auto itComp = components.begin(); itComp != components.end(); itComp++) {
                if ((*itComp)->getType() == COMP::bitmask) {
                    components.erase(itComp);
                    deleted = true;
                    break;
                }
            }

            if(deleted) {
                systemManager->notifyEntityUpdate(id, getComponentBitmask(id));
            }
        }
    }

private:
    ComponentBitMask getComponentBitmask(EntityId id);
};

}

#endif //TORTUGA_ENTITY_HPP
