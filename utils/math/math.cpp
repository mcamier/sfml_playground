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

vec2 angleToVec(double deg)
{
    double rad = toRad(deg);
    return vec2(cos(rad), sin(rad));
}

vec2 interpolate(vec2 a, vec2 b, float t)
{
    return vec2(a.x+t*(b.x-a.x), a.y+t*(b.y-a.y));
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

float vectorToDegrees(vec2 v)
{
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