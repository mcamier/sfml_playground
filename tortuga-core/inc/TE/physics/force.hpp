#ifndef TORTUGA_FORCE_HPP
#define TORTUGA_FORCE_HPP

#include "particule.hpp"
#include "../ecs/component.hpp"
#include <SFML/Window.hpp>

namespace ta {

const vec3f gravityForce3 = vec3f(0.0f, -11.0f, 0.0f);
const vec2f gravityForce2 = vec2f(0.0f, -11.0f);

/**
 * Represent the implementation of any force that could be applied to a particule
 */
class ParticuleForceGenerator {
public:
    virtual void generate(CParticule* physic, CPosition* position, const sf::Time& duration) = 0;
};

/**
 * Implementation of the gravity force
 */
class GravityForceGenerator : public ParticuleForceGenerator {
private:
    vec3f gravity;

public:
    GravityForceGenerator(vec3f gravity) : gravity(gravity) {}

    void generate(CParticule* physic, CPosition* position, const sf::Time& duration) override;
};

/**
 * Implementation of a spring force between a particule and an anchored point in space
 */
class AnchoredSpringForceGenerator : public ParticuleForceGenerator {
private:
    vec3f anchorLocation;
    float restLength;
    float springConstant;

public:
    AnchoredSpringForceGenerator(vec3f anchorLocation, float springConstant, float restLength) : anchorLocation(anchorLocation), springConstant(springConstant), restLength(restLength) {}

    void generate(CParticule* physic, CPosition* position, const sf::Time& duration) override;
};

}

#endif //TORTUGA_FORCE_HPP
