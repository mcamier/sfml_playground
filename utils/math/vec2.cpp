#include <cmath>
#include "vec2.hpp"

void vec2::invert()
{
    x = -x;
    y = -y;
}

void vec2::scale(float value) {
    this->x *= value;
    this->y *= value;
}

double vec2::magnitude()
{
    return sqrt(x*x+y*y);
}

double vec2::squareMagnitude()
{
    return x*x+y*y;
}

void vec2::normalize()
{
    double magnitude = this->magnitude();

    if (magnitude>1) {
        this->x *= ((double) 1/magnitude);
        this->y *= ((double) 1/magnitude);
    }
}

vec2 vec2::multiply(vec2 source, double scalar)
{
    return vec2(source.x*scalar, source.y*scalar);
}