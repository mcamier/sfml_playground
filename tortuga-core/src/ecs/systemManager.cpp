#include "../../inc/TE/ecs/systemManager.hpp"

#include "../../inc/TE/ecs/entity.hpp"

namespace ta {

//
//
void SystemManager::notifyEntityUpdate(EntityId id, ComponentBitMask componentBitMask) {
    for(auto it = this->systems.begin() ; it != systems.end() ; it++) {
        (*it)->registerIfCompatible(id, componentBitMask);
    }
}

void SystemManager::addSystem(ISystem* system) {
    this->systems.push_back(system);
}

void SystemManager::update(const Time & time) {
    for(auto it = this->systems.begin() ; it != systems.end() ; it++) {
        (*it)->update(time);
    }
}

}