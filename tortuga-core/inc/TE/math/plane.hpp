#ifndef FOOBAR_PLANE_HPP
#define FOOBAR_PLANE_HPP

#include "vec3.hpp"

struct plane {
    // p is a point in the plane
    vec3f p;
    // n is the normal of the plane
    vec3f n;
};

bool testPointIsOnPlane(const plane& plane, const vec3f point) {
    return 0 == vec3f::dot(plane.n, point - plane.p);
}

#endif //FOOBAR_PLANE_HPP