#include "../../inc/TE/ecs/systemManager.hpp"

#include "../../inc/TE/ecs/entity.hpp"
#include "../../inc/TE/ecs/system.hpp"
#include "../../inc/TE/message/message.hpp"

namespace ta {

//
//
SystemManager::SystemManager() {
    this->renderSystem = new RenderSystem();
    this->renderSystem->manager = this;
}

void SystemManager::notifyEntityUpdate(EntityId id, const ComponentBitMask& componentBitMask) {
    for(auto it = this->systems.begin() ; it != systems.end() ; it++) {
        (*it)->registerIfCompatible(id, componentBitMask);
    }
    this->renderSystem->registerIfCompatible(id, componentBitMask);
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
    handleEvent(time);
    // then update all the systems
    for(auto it = this->systems.begin() ; it != systems.end() ; it++) {
        (*it)->update(time);
    }
}

void SystemManager::handleEvent(const sf::Time& time) {
    for(const auto& it : this->pendingMessages) {
        EntityId target = it.first;
        auto& messages = it.second;

        for(auto& system : this->systems) {
            if(system->hasEntity(target)) {
                for(const auto& msg : messages) {
                    system->handleEvent(time, target, msg);
                }
            }
        }
    }
    this->pendingMessages.clear();
}

void SystemManager::sendMessage(EntityId receiver, const ECSMessage message) {
    REP_DEBUG("Message " << message.type << " send for entity #" << receiver, LogChannelFlag::DEFAULT)
    auto result = this->pendingMessages.find(receiver);
    if(result != this->pendingMessages.end()) {
        auto& messages = (*result).second;
        messages.push_back(message);
    } else {
        std::list<ECSMessage> messages;
        messages.push_back(message);
        this->pendingMessages.insert(std::make_pair(receiver, messages));
    }
}

void SystemManager::render(RenderTexture& renderTexture) {
    this->renderSystem->render(renderTexture);
}

}