#include "gtest/gtest.h"
#include "../include/tortuga/math/vector.hpp"

using namespace std;
using namespace ta::core;

TEST(vec2, sum) {
    vec2i a = vec2i(2, 4);
    vec2i b = vec2i(8, 2);
    vec2i result = a + b;

    EXPECT_EQ(result.x, 10);
    EXPECT_EQ(result.y, 6);

    a+=b;
    EXPECT_EQ(a.x, 10);
    EXPECT_EQ(a.y, 6);
}

TEST(vec2, subtract) {
    vec2i a = vec2i(2, 4);
    vec2i b = vec2i(8, 2);
    vec2i result = a - b;

    EXPECT_EQ(result.x, -6);
    EXPECT_EQ(result.y, 2);

    a-=b;
    EXPECT_EQ(a.x, -6);
    EXPECT_EQ(a.y, 2);
}

TEST(vec2, scale) {
    vec2i a = vec2i(2, 4);
    vec2i result = a * 3;

    EXPECT_EQ(result.x, 6);
    EXPECT_EQ(result.y, 12);

    a*=3;
    EXPECT_EQ(a.x, 6);
    EXPECT_EQ(a.y, 12);
}

TEST(vec2, normalize) {
    vec2i a = vec2i(20, 0);
    a.normalize();

    EXPECT_EQ(a.x, 1);
    EXPECT_EQ(a.y, 0);
}



TEST(vec3, sum) {
    vec3i a = vec3i(2, 4, 5);
    vec3i b = vec3i(8, 2, 5);
    vec3i result = a + b;

    EXPECT_EQ(result.x, 10);
    EXPECT_EQ(result.y, 6);
    EXPECT_EQ(result.z, 10);

    a+=b;
    EXPECT_EQ(a.x, 10);
    EXPECT_EQ(a.y, 6);
    EXPECT_EQ(a.z, 10);
}

TEST(vec3, subtract) {
    vec3i a = vec3i(2, 4, 5);
    vec3i b = vec3i(8, 2, 5);
    vec3i result = a - b;

    EXPECT_EQ(result.x, -6);
    EXPECT_EQ(result.y, 2);
    EXPECT_EQ(result.z, 0);

    a-=b;
    EXPECT_EQ(a.x, -6);
    EXPECT_EQ(a.y, 2);
    EXPECT_EQ(a.z, 0);
}

TEST(vec3, scale) {
    vec3i a = vec3i(2, 4, 5);
    vec3i result = a * 3;

    EXPECT_EQ(result.x, 6);
    EXPECT_EQ(result.y, 12);
    EXPECT_EQ(result.z, 15);

    a*=3;
    EXPECT_EQ(a.x, 6);
    EXPECT_EQ(a.y, 12);
    EXPECT_EQ(a.z, 15);
}