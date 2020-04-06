#ifndef TORTUGA_COMPONENT_HPP
#define TORTUGA_COMPONENT_HPP

#include <stdexcept>

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

};

COMPONENT_DEF(CKinetic)

public:
    vec2f movement = vec2f(-1, 0);

};


COMPONENT_DEF(CRenderer)

public:
    Origin origin = Origin::CENTER;
    IRenderable* renderable;
};


COMPONENT_DEF(CHitbox)

public:
    Origin origin = Origin::CENTER;
    ICollider* collider;

};


}

#endif //TORTUGA_COMPONENT_HPP
