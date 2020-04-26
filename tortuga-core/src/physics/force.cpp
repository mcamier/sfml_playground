#include "../../inc/TE/physics/force.hpp"

#include "../../inc/TE/ecs/base.hpp"

namespace ta {

void GravityForceGenerator::generate(CParticule* physic, CPosition* position, const sf::Time& duration) {
    if (physic->hasInfiniteMass()) return;
    physic->addForce(physic->getMass() * gravity);
}

void AnchoredSpringForceGenerator::generate(CParticule* physic, CPosition* position, const sf::Time& duration) {
    vec3f force = position->position;
    force -= anchorLocation;

    float magnitude = force.length();
    magnitude = (restLength - magnitude) * springConstant;

    force.normalize();
    force *= magnitude;
    physic->addForce(force);
}

}
