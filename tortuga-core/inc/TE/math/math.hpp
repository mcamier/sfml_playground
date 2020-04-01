#ifndef FOOBAR_MATH_HPP
#define FOOBAR_MATH_HPP

#include "math.h"
#include "vec2.hpp"
#include "rect.hpp"
#include "vec3.hpp"

#define HALF_PI 1.570796327
#define PI 3.141592654
#define TWO_PI 6.283185307

namespace ta {

double toRad(int degree);

int toDeg(double rad);

vec2f angleToVec(double deg);

template <typename T>
vec2<T> interpolate(vec2<T> a, vec2<T> b, float t);

template <typename T>
T square(T x);

int clamp(int x, int min, int max);

template <typename T>
float vectorToDegrees(vec2<T> v) {
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

vec2f getPointOnArc(int angle, float radius);

vec3f mean(vec3f pts[], int num_pts);

bool isPointInsideRect(const vec2f& pt, const rectf& rect);

}  // namespace ta

#endif  // FOOBAR_MATH_HPP
