#include <iostream>
#include "../utils/math/vector.hpp"

using namespace std;

void print_vector(const vec2f& v) {
    cout << v.x << ", " << v.y << endl;
}

void print_vector(const vec3f& v) {
    cout << v.x << ", " << v.y << ", " << v.z << endl;
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

    // compute the determinant of the denominator for the cramer's rule equation system
    float denom = d00 * d11 - d10 * d01;
    bary.x = (d20*d11-d10*d21) / denom;
    bary.y = (d00*d21-d20*d01) / denom;
    bary.z = 1 - (bary.x + bary.y);

    return bary;
}

bool testPointInsideTriangle(const vec3f& a, const vec3f& b, const vec3f& c, const vec3f& p) {
    vec3f weight = barycentric(a,b,c,p);
    return (weight.x >= .0f && weight.y >= .0f && weight.x+weight.y<=1.0f);
}

int main(int argc, char* argv[]) {

    cout << "HelloWorld" << endl;

    vec2f v1(2, 5);
    vec2f v2(9, 4);

    vec2f v3 = v1 + v2;
    vec2f v4 = -v2;
    vec2f v5 = v2 - v1;

    cout << "v1: ";
    print_vector(v1);
    cout << "v2: ";
    print_vector(v2);
    cout << "v3: ";
    print_vector(v3);
    cout << "v4: ";
    print_vector(v4);
    cout << "v5: ";
    print_vector(v5);

    cout << "3 * v2 = ";
    vec2f v6 = v2 * 3.5f;
    print_vector(v6);

    //---------------------------------
    vec3f a(1, 0, 0);
    vec3f b(0, 1, 0);
    vec3f c(0, 0, 1);
    vec3f p(.5f, .5f, 1.0f);

    vec3f claude = barycentric(a, b, c, p);
    cout << "barycenter= ";
    print_vector(claude);
    cout << "test p in triangle: " << testPointInsideTriangle(a,b,c,p) << endl;

    vec3f p2(3, 3, 1);
    cout << "test p2 in triangle: " << testPointInsideTriangle(a,b,c,p2) << endl;

    return 0;

}