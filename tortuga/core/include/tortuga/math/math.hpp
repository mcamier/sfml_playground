#ifndef FOOBAR_MATH_HPP
#define FOOBAR_MATH_HPP

#include "math.h"
#include "vector.hpp"
#include "rect.hpp"
#include "vector.hpp"

#define HALF_PI 1.570796327
#define PI      3.141592654
#define TWO_PI  6.283185307

namespace ta::core {

/**
 * Convert a value from degree to radian
 *
 * @param degree value to convert
 * @return result as radian
 */
double toRad(int degree);

/**
 * Convert a value from radian to degree
 *
 * @param rad value to convert
 * @return result as degree
 */
int toDeg(double rad);

/**
 * Convert a 2D angle to a normalized vector
 *
 * @param deg angle to convert
 * @return result as a vector
 */
vec3f angleToVec(double deg);

/**
 * Interpolate two values a and b given f
 * f must be a value between 0 and 1
 *
 * @tparam T numerical class
 * @param a interpolation begin value
 * @param b interpolation end value
 * @param t amount of interpolation between 0 and 1
 * @return interpolated value
 */
template <typename T>
vector<T> interpolate(vector<T> a, vector<T> b, float t);

/**
 * Mulitply a number value by itself
 *
 * @tparam T numerical class
 * @param x number to square
 * @return
 */
template <typename T>
T square(T x);

/**
 * Guarantee the value x is between min and max numerical bounds
 * @tparam T numerical class
 * @param x value to clamp
 * @param min min bound
 * @param max max bound
 * @return clamped value
 */
template<typename T>
T clamp(T x, T min, T max);

template <typename T>
float vectorToDegrees(vector<T> v) {
    if (v.x == 0) {
        if (v.y > 0) {
            return 90;
        } else if (v.y < 0) {
            return 270;
        } else {
            return 0;
        }
    } else if (v.y == 0) {
        if (v.x >= 0) {
            return 0;
        } else {
            return 180;
        }
    } else {
        float result = atanf(v.y / v.x) * 180 / PI;
        if (v.x < 0 && v.y < 0) {
            result += 180;
        } else if (v.x < 0) {
            result += 180;
        } else if (v.y < 0) {
            result = result + 360;
        }
        return result;
    }
}

template <typename T>
float vectorToDegrees(vec3<T> v) {
    if (v.x == 0) {
        if (v.y > 0) {
            return 90;
        } else if (v.y < 0) {
            return 270;
        } else {
            return 0;
        }
    } else if (v.y == 0) {
        if (v.x >= 0) {
            return 0;
        } else {
            return 180;
        }
    } else {
        float result = atanf(v.y / v.x) * 180 / PI;
        if (v.x < 0 && v.y < 0) {
            result += 180;
        } else if (v.x < 0) {
            result += 180;
        } else if (v.y < 0) {
            result = result + 360;
        }
        return result;
    }
}

vec3f barycentric(const vec3f& a, const vec3f& b, const vec3f& c, const vec3f& p);

bool isOutsideCircle(float x, float y, float radius);

bool isInsideCircle(float x, float y, float radius);

vec3f getPointOnArc(int angle, float radius);

vec3f mean(vec3f pts[], int num_pts);

bool isPointInsideRect(const vec2f& pt, const rectf& rect);

}  // namespace ta

#endif  // FOOBAR_MATH_HPP
