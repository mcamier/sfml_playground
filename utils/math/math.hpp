#ifndef FOOBAR_MATH_HPP
#define FOOBAR_MATH_HPP

#include "vec2.hpp"
#include "math.h"

#define PI 3.14159265

double toRad(double degree);

double toDeg(double rad);

vec2 angleToVec(double deg);

vec2 interpolate(vec2 a, vec2 b, float t);

template<typename T>
T square(T x);

float vectorToDegrees(vec2 v);

#endif //FOOBAR_MATH_HPP
