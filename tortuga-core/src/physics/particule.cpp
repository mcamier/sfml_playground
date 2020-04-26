#include "../../inc/TE/physics/particule.hpp"

#include "../../inc/TE/ecs/base.hpp"

namespace ta {

COMPONENT_IMPL(CParticule)

CParticule::CParticule(float mass) {
    setMass(mass);
}

void CParticule::setMass(float mass) {
    if (mass == 0.0f) {
        invertedMass = 0;
    } else {
        invertedMass = 1.0f / mass;
    }
}

float CParticule::getInvertedMass() const {
    return this->invertedMass;
}

float CParticule::getMass() const {
    return 1.0f / this->invertedMass;
}

void CParticule::addForce(vec3f force) {
    forceAccumulator += force;
}

void CParticule::clearForceAccumulator() {
    forceAccumulator = vec3f(0, 0, 0);
}

bool CParticule::hasInfiniteMass() const {
    return invertedMass == 0.0f;
}
}
