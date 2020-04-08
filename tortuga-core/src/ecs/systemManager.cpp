#include "../../inc/TE/ecs/systemManager.hpp"

#include "../../inc/TE/ecs/entity.hpp"
#include "../../inc/TE/ecs/system.hpp"

namespace ta {

//
//
void SystemManager::notifyEntityUpdate(EntityId id, ComponentBitMask componentBitMask) {
    for(auto it = this->systems.begin() ; it != systems.end() ; it++) {
        (*it)->registerIfCompatible(id, componentBitMask);
    }
}

void SystemManager::addSystem(ISystem* system) {
    system->manager = this;
    this->systems.push_back(system);

    // SystemManager is thighly coupled to the EntityManager because of the following code
    // consider cleaning this implementation
    auto itEntities = this->entityManager->entityComponents.begin();
    for(; itEntities != this->entityManager->entityComponents.end() ; itEntities++) {
        EntityId id = itEntities->first;
        auto mask = this->entityManager->getComponentBitmask(id);
        system->registerIfCompatible(id, mask);
    }
}

void SystemManager::update(const Time & time) {
    handleEvent();
    // then update all the systems
    for(auto it = this->systems.begin() ; it != systems.end() ; it++) {
        (*it)->update(time);
    }

}

void SystemManager::handleEvent() {

}

}