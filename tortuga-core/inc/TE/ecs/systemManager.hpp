#ifndef TORTUGA_SYSTEM_MANAGER_HPP
#define TORTUGA_SYSTEM_MANAGER_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <set>
#include <unordered_map>
#include <string>
#include "../core/IUpdatable.hpp"
#include "../ecs/base.hpp"
#include "../logger.hpp"
#include "component.hpp"

namespace ta {

using namespace utils;

using std::list;
using std::string;
using std::unordered_map;

class ISystem;
class EntityManager;
class ECSMessage;
class RenderSystem;

//
//
class SystemManager : public IUpdatable, public IRenderable {
    friend class EntityManager;
    friend class ISystem;

private:
    EntityManager* entityManager;
    list<ISystem*> systems;
    RenderSystem* renderSystem;
    unordered_map<EntityId, list<ECSMessage>> pendingMessages;

    void notifyEntityUpdate(EntityId id, const ComponentBitMask& componentBitMask);

public:
    SystemManager();

    void addSystem(ISystem* system);

    void update(const Time&) override;

    void render(RenderTexture &) override;

    void handleEvent(const sf::Time& time);

    void sendMessage(EntityId receiver, const ECSMessage message);
};

}

#endif
