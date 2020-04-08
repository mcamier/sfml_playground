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
    friend class SystemManager;

private:
    SystemManager* systemManager;
    EntityId lastEntityId = 0;
    map<EntityId, list<IComponent*>> entityComponents;

public:
    EntityManager(SystemManager* systemManager) : systemManager(systemManager) {
        systemManager->entityManager = this;
    }

    EntityId addEntity();

    void removeEntity(EntityId id);

    void addComponent(EntityId id, IComponent* component);

    template<typename COMP>
    COMP* getComponent(EntityId entityId) {
        auto it = entityComponents.find(entityId);
        if(it != entityComponents.end()) {
            auto& components = (*it).second;
            for (auto itComp = components.begin(); itComp != components.end(); itComp++) {
                if ((*itComp)->getType() == COMP::bitmask) {
                    IComponent* comp = (*itComp);
                    return static_cast<COMP*>(comp);
                }
            }
        }

        throw std::runtime_error("no component reference found to return");
    }

    // TODO maybe consider doing a soft delete of the component until the end of the frame
    // (update loop), then hard delete before the next frame update
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
