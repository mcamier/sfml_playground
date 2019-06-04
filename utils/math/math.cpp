#include "math.hpp"

#include <math.h>

double toRad(int degree) { return degree * PI / 180.0; }

int toDeg(double rad) { return rad * 180.0 / PI; }

vec2f angleToVec(double deg) {
  double rad = toRad(deg);
  return vec2f(cos(rad), sin(rad));
}

template <>
vec2i interpolate(vec2i a, vec2i b, float t) {
  return vec2i(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
}

template <>
vec2f interpolate(vec2f a, vec2f b, float t) {
  return vec2f(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
}

template <>
int square(int x) {
  return x * x;
}

template <>
float square(float x) {
  return x * x;
}

template <>
double square(double x) {
  return x * x;
}

int clamp(int x, int min, int max) {
  return (x < min) ? min : (x > max) ? max : x;
}

vec3f barycentric(vec3f a, vec3f b, vec3f c, vec3f p) {
  vec3f bary;
  vec3f v0 = b - a;
  vec3f v1 = c - a;
  vec3f v2 = p - a;

  float d00 = vec3f::dot(v0, v0);
  float d11 = vec3f::dot(v1, v1);
  float d10 = vec3f::dot(v1, v0);
  float d01 = vec3f::dot(v0, v1);

  float d20 = vec3f::dot(v2, v0);
  float d21 = vec3f::dot(v2, v1);

  // use cramer's rule to resolve the equations system

  // compute the determinant of the denominator for the cramer's rule equation
  // system
  float denom = d00 * d11 - d10 * d01;
  bary.y = (d20 * d11 - d10 * d21) / denom;
  bary.z = (d00 * d21 - d20 * d01) / denom;
  bary.x = 1 - (bary.y + bary.z);

  return bary;
}

bool isOutsideCircle(float x, float y, float radius) {
  return ((x * x) + (y * y)) > square(radius);
}

bool isInsideCircle(float x, float y, float radius) {
  return ((x * x) + (y * y)) <= square(radius);
}

vec2f getPointOnArc(float angle, float radius) {
  vec2f v = angleToVec(angle);
  v.y = -v.y;
  v *= radius;
  return v;
}

vec3f mean(vec3f pts[], int num_pts) {
  vec3f mean(0, 0, 0);
  for (int i = 0; i < num_pts; i++) {
    mean += pts[i];
  }
  mean *= 1.0f / (float)num_pts;

  return mean;
}