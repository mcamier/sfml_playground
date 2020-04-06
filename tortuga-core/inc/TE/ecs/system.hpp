#ifndef TORTUGA_SYSTEM_HPP
#define TORTUGA_SYSTEM_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <set>
#include <string>
#include "../core/IUpdatable.hpp"
#include "../ecs/base.hpp"
#include "../logger.hpp"
#include "component.hpp"

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
class ISystem : public IUpdatable {
public:
    virtual void registerIfCompatible(EntityId id, ComponentBitMask flag) = 0;

    virtual const string& getName() = 0;
};


//
//
template<typename... COMPS>
class AbstractSystem : public ISystem {
private:
    SystemComponentFlag<COMPS...> systemComponenflag;
    set<EntityId> entitiesManaged;

public:
    void registerIfCompatible(EntityId id, ComponentBitMask flag) override {
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
};


//
//
class RenderingSystem : public AbstractSystem<CPosition, CRenderer> {
private:
    const string name = "RenderingSystem";

public:
    void update(const Time&) override;

    const string& getName() override;
};


//
//
class CollisionSystem : public AbstractSystem<CPosition, CHitbox> {
private:
    const string name = "CollisionSystem";

public:
    void update(const Time&) override;

    const string& getName() override;
};


//
//
class KineticSystem : public AbstractSystem<CPosition, CKinetic> {
private:
    const string name = "KineticSystem";

public:
    void update(const Time&) override;

    const string& getName() override;
};


}

#endif //TORTUGA_SYSTEM_HPP
