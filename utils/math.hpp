#ifndef FOOBAR_MATH_HPP
#define FOOBAR_MATH_HPP

#include <cmath>
#include "vec2.hpp"

#define PI 3.14159265

double toRad(double degree)
{
    return degree*PI/180.0;
}

double toDeg(double rad)
{
    return rad*180.0/PI;
}

vec2 angleToVec(double deg)
{
    double rad = toRad(deg);
    return vec2(cos(rad), sin(rad));
}

vec2 interpolate(vec2 a, vec2 b, float t)
{
    return vec2(a.x+t*(b.x-a.x), a.y+t*(b.y-a.y));
}

#endif //FOOBAR_MATH_HPP
