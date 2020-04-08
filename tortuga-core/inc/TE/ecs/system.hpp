#ifndef TORTUGA_ECS_SYSTEM_HPP
#define TORTUGA_ECS_SYSTEM_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <set>
#include <string>
#include "../core/IUpdatable.hpp"
#include "../ecs/base.hpp"
#include "../logger.hpp"
#include "component.hpp"
#include "observer.hpp"
#include "systemManager.hpp"
#include "../message/message.hpp"

namespace ta {

using namespace utils;

using std::set;
using std::string;




template<typename T, typename... C>
struct SystemComponentFlag {
    T t;
    int getValue() {
        SystemComponentFlag<C...> f;
        return t.bitmask | f.getValue();
    }
};

template<typename T>
struct SystemComponentFlag<T> {
    T t;
    int getValue() { return t.bitmask; }
};


//
//
class ISystem : public IUpdatable, public Observer {
    friend class SystemManager;

protected:
    SystemManager* manager;

public:
    virtual void registerIfCompatible(EntityId id, ComponentBitMask flag) = 0;

    virtual void sendMessage(EntityId target, ECSMessage message) = 0;

    virtual const string& getName() = 0;

    virtual void handleEvent(const sf::Time& time, EntityId target, ECSMessage message) = 0;

    virtual bool hasEntity(EntityId target) = 0;

    template<typename T>
    T* getComponent(EntityId entityId) {
        return manager->entityManager->getComponent<T>(entityId);
    }
};

//
//
template<typename... COMPS>
class AbstractSystem : public ISystem {
protected:
    SystemComponentFlag<COMPS...> systemComponenflag;
    set<EntityId> entitiesManaged;

public:
    virtual void preUpdate(const sf::Time& time) {};

    virtual void update(const sf::Time& time, EntityId entityId) = 0;

    virtual void postUpdate(const sf::Time& time) {};

    void update(const sf::Time& time) final {
        this->preUpdate(time);
        for(auto& entityId : entitiesManaged) {
            this->update(time, entityId);
        }
        this->postUpdate(time);
    }

    void registerIfCompatible(EntityId id, ComponentBitMask flag) final {
        int maskAsInt = systemComponenflag.getValue();

        if ((flag & maskAsInt) == maskAsInt) {
            auto itInsertion = this->entitiesManaged.insert(id);
            if (itInsertion.second) {
                REP_DEBUG("entity #" << id << " registered in system " << this->getName(), LogChannelFlag::DEFAULT);
            }
        } else {
            auto it = this->entitiesManaged.find(id);
            if (it != this->entitiesManaged.end()) {
                this->entitiesManaged.erase(it);
                REP_DEBUG("entity #" << id << " unregistered from system " << this->getName(), LogChannelFlag::DEFAULT);
            }
        }
    }

    void sendMessage(EntityId target, ECSMessage message) final {
        manager->sendMessage(target, message);
    }

    bool hasEntity(EntityId target) final {
        auto it = this->entitiesManaged.find(target);
        return it != this->entitiesManaged.end();
    }
};

//
//
class RenderSystem : public AbstractSystem<CPosition, CRenderer> {
    friend class SystemManager;

private:
    const string name = "RenderSystem";

public:
    void render(RenderTexture &);

    void update(const Time& time, EntityId entityId) override;

    void handleEvent(const sf::Time& time, EntityId target, ECSMessage msg) override;

    const string& getName() override;
};

}

#endif //TORTUGA_ECS_SYSTEM_HPP
