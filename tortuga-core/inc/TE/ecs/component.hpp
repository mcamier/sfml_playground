#ifndef TORTUGA_COMPONENT_HPP
#define TORTUGA_COMPONENT_HPP

#include <stdexcept>
#include <functional>

#include "../../TE/math/vec2.hpp"
#include "../../TE/core/origin.hpp"
#include "../../TE/Collider.hpp"
#include "../../TE/core/IRenderable.hpp"
#include "../../TE/ecs/base.hpp"

namespace ta {

class IComponent {
public:
    virtual ComponentBitMask getType() = 0;

};

COMPONENT_DEF(CPosition)
public:
    vec2f position = vec2f(0, 0);

    CPosition(float x, float y) : position(vec2f(x, y)) {}

};

COMPONENT_DEF(CKinetic)
public:
    vec2f direction = vec2f(-1, 0);
    float speed = 1;

    CKinetic(float directionx, float directiony, float speed) : speed(speed), direction(vec2f(directionx, directiony)) {}

};


COMPONENT_DEF(CRenderer)
public:
    Origin origin = Origin::CENTER;
    std::function<void(const CPosition&, sf::RenderTexture&)> drawCallback;

    CRenderer(std::function<void(const CPosition&, sf::RenderTexture&)> drawCallback) : drawCallback(drawCallback) {}
};


COMPONENT_DEF(CHitbox)
public:
    Origin origin = Origin::CENTER;
    ICollider* collider;

};

}

#endif //TORTUGA_COMPONENT_HPP
