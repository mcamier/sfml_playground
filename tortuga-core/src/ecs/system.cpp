#include "../../inc/TE/ecs/system.hpp"

#include <SFML/Graphics.hpp>

namespace ta {

void RenderSystem::render(sf::RenderTexture &renderTexture) {
    for(EntityId id : this->entitiesManaged) {
        auto* pos = getComponent<CPosition>(id);
        auto* renderer = getComponent<CRenderer>(id);

        renderer->drawCallback(*pos, renderTexture);
    }
}

void RenderSystem::update(const Time& time, EntityId entityId) {
}

void RenderSystem::handleEvent(const sf::Time& time, EntityId target, ECSMessage msg) {
}

const string& RenderSystem::getName() {
    return name;
}

}
