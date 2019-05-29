#include "math.hpp"

#include <math.h>

double toRad(double degree)
{
    return degree*PI/180.0;
}

double toDeg(double rad)
{
    return rad*180.0/PI;
}

vec2f angleToVec(double deg)
{
    double rad = toRad(deg);
    return vec2f(cos(rad), sin(rad));
}

template<>
vec2i interpolate(vec2i a, vec2i b, float t)
{
    return vec2i(a.x+t*(b.x-a.x), a.y+t*(b.y-a.y));
}

template<>
vec2f interpolate(vec2f a, vec2f b, float t)
{
    return vec2f(a.x+t*(b.x-a.x), a.y+t*(b.y-a.y));
}


template<>
int square(int x) {
    return x * x;
}

template<>
float square(float x) {
    return x * x;
}

template<>
double square(double x) {
    return x * x;
}

int clamp(int x, int min, int max) {
    return (x < min) ? min : (x > max) ? max : x;
}