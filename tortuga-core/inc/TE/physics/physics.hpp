#ifndef TORTUGA_PHYSICS_HPP
#define TORTUGA_PHYSICS_HPP

#include "../math/math.hpp"
#include "../ecs/system.hpp"
#include "../ecs/component.hpp"
#include "particule.hpp"
#include "force.hpp"

#include <list>

namespace ta {

using namespace std;


struct Contact {
    //CParticule* p1;
    //CParticule* p2;
    //float separatingVelocity;
    //vec3f contactNormal;
};

/**
 *
 */
class ParticuleContactGenerator {
public:
    virtual void setContact(Contact& contactToSet) = 0;
};




/**
 *
 */
class BasicPhysicSystem : public AbstractSystem<CPosition, CParticule> {
private:
    const string name = "BasicPhysicSystem";
    std::map<EntityId, list<ParticuleForceGenerator*>> forceGenerators;

public:
    BasicPhysicSystem() {}

    void preUpdate(const Time& duration) override {
        /**
         * Before physics computation for the current frame, we have to reset the
         * force accumulator for every particule components
         */
        for(EntityId id : entitiesManaged) {
            auto* physic = getComponent<CParticule>(id);
            physic->clearForceAccumulator();
        }

        /**
         * Apply all registered forces upon particules
         */
        for(auto& entry : forceGenerators) {
            EntityId entityId = entry.first;

            auto* position = getComponent<CPosition>(entityId);
            auto* physic = getComponent<CParticule>(entityId);

            for(auto& generator : entry.second) {
                generator->generate(physic, position, duration);
            }
        }
    }

    void update(const Time& time, EntityId entityId) override {
        auto* position = getComponent<CPosition>(entityId);
        auto* physic = getComponent<CParticule>(entityId);

        /**
         *  Based on forces applied to particules, computes their new positions
         */
        integrate(position, physic, time);
    }

    void handleEvent(const sf::Time& time, EntityId target, ECSMessage msg) override {}

    const string& getName() override {
        return name;
    }

    void addGenerator(EntityId id, ParticuleForceGenerator* forceGenerator) {
        auto it = forceGenerators.find(id);
        if(it == forceGenerators.end()) {
            list<ParticuleForceGenerator*> generators;
            generators.push_back(forceGenerator);
            forceGenerators.insert(make_pair(id, std::move(generators)));
        } else {
            auto& list = it->second;
            list.push_back(forceGenerator);
        }
    }

private:
    void integrate(CPosition* position, CParticule* physic, const sf::Time& time) {
        if(physic->getInvertedMass() == 0.0f) return;

        float duration = time.asMilliseconds() / 1000.0f;
        ASSERT(secondsElapsed > 0.0f)

        position->position.addScaledVector(duration, physic->velocity);

        physic->velocity.addScaledVector(duration, physic->getInvertedMass() * physic->forceAccumulator);

        // apply damping
        physic->velocity *= powf(physic->damping, duration);
        physic->clearForceAccumulator();
    }
};

}

#endif //TORTUGA_PHYSICS_HPP