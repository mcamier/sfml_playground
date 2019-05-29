#ifndef FOOBAR_MATH_HPP
#define FOOBAR_MATH_HPP

#include "vector.hpp"
#include "math.h"

#define TWO_PI 6.283185307
#define PI 3.141592654
#define HALF_PI 1.570796327

double toRad(double degree);

double toDeg(double rad);

vec2f angleToVec(double deg);

template<typename T>
vec2<T> interpolate(vec2<T> a, vec2<T> b, float t);

template<typename T>
T square(T x);

int clamp(int x, int min, int max);

template<typename T>
float vectorToDegrees(vec2<T> v) {
    if (v.x==0) {
        if (v.y>0) {
            return 90;
        }
        else if (v.y<0) {
            return 270;
        }
        else {
            return 0;
        }
    }
    else if (v.y==0) {
        if (v.x>=0) {
            return 0;
        }
        else {
            return 180;
        }
    }
    else {
        float result = atanf(v.y/v.x) * 180 / PI;
        if(v.x < 0 && v.y < 0) {
            result += 180;
        } else if(v.x < 0) {
            result += 180;
        } else if(v.y < 0) {
            result += 270;
        }
        return result;
    }
}

#endif //FOOBAR_MATH_HPP
