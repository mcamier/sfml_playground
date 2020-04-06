#include "../../inc/TE/ecs/entity.hpp"

#include <utility>
#include <algorithm>

#include "../../inc/TE/ecs/system.hpp"

namespace ta {

using namespace std;

EntityId EntityManager::addEntity() {
    return lastEntityId++;
}

void EntityManager::removeEntity(EntityId id) {
    auto it = entityComponents.find(id);
    if(it != entityComponents.end()) {
        entityComponents.erase(it);
    }

    systemManager->notifyEntityUpdate(id, getComponentBitmask(id));
}

void EntityManager::addComponent(EntityId id, IComponent* component) {
    auto it = entityComponents.find(id);
    if(it == entityComponents.end()) {
        list<IComponent*> components;
        components.push_back(component);
        entityComponents.insert(make_pair(id, std::move(components)));
    } else {
        auto& components = (*it).second;
        for (auto itComp = components.begin(); itComp != components.end(); itComp++) {
            if ((*itComp)->getType() == component->getType()) {
                components.erase(itComp);
                break;
            }
        }
        components.push_back(component);
    }

    systemManager->notifyEntityUpdate(id, getComponentBitmask(id));
}

ComponentBitMask EntityManager::getComponentBitmask(EntityId id) {
    ComponentBitMask result;

    auto it = entityComponents.find(id);
    if(it != entityComponents.end()) {
        list<IComponent*> components = (*it).second;
        for (auto itComp = components.begin(); itComp != components.end(); itComp++) {
            ComponentBitMask mask = (*itComp)->getType();
            result = result | mask;
        }
    }
    return result;
}

}