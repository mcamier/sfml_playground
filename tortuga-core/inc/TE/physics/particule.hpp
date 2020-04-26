#ifndef TORTUGA_PARTICULE_HPP
#define TORTUGA_PARTICULE_HPP

#include "../math/math.hpp"
#include "../ecs/system.hpp"
#include "../ecs/component.hpp"

#include <list>

namespace ta {

using namespace std;

/**
 * Class used by the EntityComponent System in order to simulate simple particule physic
 */
COMPONENT_DEF(CParticule)
public:
    vec3f velocity; // m/s
    vec3f acceleration;
    float damping = .8f;
    vec3f forceAccumulator;
private:
    /**
     * if the mass is infinite, the particule will never react to any forces
     * to simulate this, we store 0 as the invertedMass
     */
    float invertedMass;

public:
    CParticule(float mass);

    void setMass(float mass);

    float getInvertedMass() const;

    float getMass() const;

    void addForce(vec3f force);

    void clearForceAccumulator();

    bool hasInfiniteMass() const;
};

}

#endif //TORTUGA_PHYSICS_HPP