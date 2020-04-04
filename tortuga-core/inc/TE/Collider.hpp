#ifndef TORTUGA_COLLIDER_HPP
#define TORTUGA_COLLIDER_HPP

namespace ta {

class CollisionInfo {};

class ICollider {
public:
    CollisionInfo intersect(ICollider *other) {
        return CollisionInfo();
    }
};

}

#endif //TORTUGA_COLLIDER_HPP
