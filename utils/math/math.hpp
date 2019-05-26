#ifndef FOOBAR_MATH_HPP
#define FOOBAR_MATH_HPP

#include "vec2.hpp"

#define PI 3.14159265

double toRad(double degree);

double toDeg(double rad);

vec2 angleToVec(double deg);

vec2 interpolate(vec2 a, vec2 b, float t);

#endif //FOOBAR_MATH_HPP
