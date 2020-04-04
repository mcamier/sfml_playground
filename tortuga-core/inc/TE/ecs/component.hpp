#ifndef TORTUGA_COMPONENT_HPP
#define TORTUGA_COMPONENT_HPP

#include "../../TE/math/vec2.hpp"
#include "../../TE/core/origin.hpp"
#include "../../TE/Collider.hpp"
#include "../../TE/core/IRenderable.hpp"

namespace ta {

class IComponent {

};

class CPosition : public IComponent {
public:
    vec2f position = vec2f(0, 0);
};

class CKinetic : public IComponent {
public:
    vec2f movement = vec2f(-1, 0);
};

class CRenderer : public IComponent {
public:
    Origin origin;
    IRenderable* renderable;
};

class CHitbox : public IComponent {
public:
    Origin origin;
    ICollider* collider;
};


}

#endif //TORTUGA_COMPONENT_HPP
