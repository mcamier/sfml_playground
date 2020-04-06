#include <iostream>
#include "TE/math/math.hpp"
#include "TE/math/plane.hpp"
#include "TE/math/vec3.hpp"

#include "TE/resource/resource_info.hpp"
#include "TE/resource/resource_service.hpp"
#include "TE/ecs/ecs.hpp"

using namespace std;
using namespace ta;

class ResourceManifest {
public:
    static const resource_info FONT;
    static const resource_info BOOM;
    static const resource_info HIT;

    static const int _COUNT;
    static const resource_info _ALL[];
};

void print_vector(const vec2f& v) { cout << v.x << ", " << v.y << endl; }

void print_vector(const vec3f& v) {
    cout << v.x << ", " << v.y << ", " << v.z << endl;
}

bool testPointInsideTriangle(const vec3f& a, const vec3f& b, const vec3f& c,
                             const vec3f& p) {
    vec3f weight = barycentric(a, b, c, p);
    return (weight.y >= .0f && weight.z >= .0f && weight.y + weight.z <= 1.0f);
}

int main(int argc, char* argv[]) {
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
    vec3f a(3, 3, 0);
    vec3f b(0, 0, 0);
    vec3f c(6, 0, 0);
    vec3f p(.5f, .5f, 1.0f);

    cout << "barycenter vec3f(0, 3, 0)= ";
    print_vector(barycentric(a, b, c, vec3f(0, 3, 0)));

    cout << "barycenter vec3f(3, -3, 0)= ";
    print_vector(barycentric(a, b, c, vec3f(3, -3, 0)));

    cout << "barycenter vec3f(3, 3, 2)= ";
    print_vector(barycentric(a, b, c, vec3f(3, 3, 2)));

    cout << testPointInsideTriangle(a, b, c, vec3f(3, 3, 2));

    plane pl;
    pl.p = vec3f(0, 0, 0);
    pl.n = vec3f(0, 1, 0);

    cout << "testPointIsOnPlane(pl, vec3f(1, 0, 3)) => "
         << testPointIsOnPlane(pl, vec3f(1, 0, 3)) << endl;
    cout << "testPointIsOnPlane(pl, vec3f(1, 1, 3)) => "
         << testPointIsOnPlane(pl, vec3f(1, 1, 3)) << endl;

    vec3f v11(2, 2, 0);
    vec3f v12(2, 0, 0);
    vec3f v13(0, 0, 0);
    vec3f v14(0, 2, 0);
    vec3f pts[4] = {v11, v12, v13, v14};
    vec3f meanPt = mean(pts, 4);
    cout << "mean point: ";
    print_vector(meanPt);

    //--------------




}