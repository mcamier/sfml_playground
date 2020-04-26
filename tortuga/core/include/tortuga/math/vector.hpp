#ifndef FOOBAR_VEC2_HPP
#define FOOBAR_VEC2_HPP

#include <math.h>

namespace ta::core {

/**
 * 2 dimensions Vector class
 * @tparam T
 */
template<typename T>
class vector {
public:
    T x;
    T y;

    vector() : x(0), y(0) {}

    vector(T x, T y) : x(x), y(y) {}

    vector(const vector& vec) : x(vec.x), y(vec.y) {}

    vector<T> operator+(const vector<T>& right) const {
        return vector<T>(this->x + right.x, this->y + right.y);
    }

    vector<T> operator-(const vector<T>& right) const {
        return vector<T>(this->x - right.x, this->y - right.y);
    }

    vector<T> operator*(const T& right) const {
        return vector<T>(this->x * right, this->y * right);
    }

    void operator+=(const vector<T>& right) const {
        this->x += right.x;
        this->y += right.y;
    }

    void operator-=(const vector<T>& right) const {
        this->x -= right.x;
        this->y -= right.y;
    }

    void operator*=(const T& right) const {
        this->x *= right;
        this->y *= right;
    }

    vector<T> operator-() const { return vector<T>(-this->x, -this->y); }

    /**
     * Scalar product
     * @param scalar
     */
    void operator*=(T scalar) {
        this->x *= scalar;
        this->y *= scalar;
    }

    void operator+=(vector<T> right) {
        this->x += right.x;
        this->y += right.y;
    }

    void operator-=(vector<T> right) {
        this->x -= right.x;
        this->y -= right.y;
    }

    static T dot(const vector<T> v1, const vector<T> v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    void addScaledVector(float scale, const vector <T>& vector) {
        this->x += scale * vector.x;
        this->y += scale * vector.y;
    }

    double length() { return sqrt(x * x + y * y); }

    double squareLength() { return x * x + y * y; }

    void normalize() {
        double l = this->length();
        if (l > 1) {
            this->x *= ((double) 1 / l);
            this->y *= ((double) 1 / l);
        }
    }
};

template<typename T>
vector<T> operator*(int s, vector<T> v) {
    return vector<T>(v.x * s, v.y * s);
}

template<typename T>
vector<T> operator*(float s, vector<T> v) {
    return vector<T>(v.x * s, v.y * s);
}

template<typename T>
vector<T> operator*(double s, vector<T> v) {
    return vector<T>(v.x * s, v.y * s);
}

template<typename T>
vector<T> operator*(vector<T> v, int s) {
    return vector<T>(v.x * s, v.y * s);
}

template<typename T>
vector<T> operator*(vector<T> v, float s) {
    return vector<T>(v.x * s, v.y * s);
}

template<typename T>
vector<T> operator*(vector<T> v, double s) {
    return vector<T>(v.x * s, v.y * s);
}

typedef vector<int> vec2i;
typedef vector<float> vec2f;
typedef vector<double> vec2d;


/**
 * 3 dimensions Vector class
 * @tparam T
 */
template<typename T>
class vec3 {
public:
    T x;
    T y;
    T z;

    vec3() : x(0), y(0), z(0) {}

    vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    vec3(const vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {}

    vec3<T> operator+(const vec3<T>& right) const {
        return vec3<T>(this->x + right.x, this->y + right.y, this->z + right.z);
    }

    vec3<T> operator-(const vec3<T>& right) const {
        return vec3<T>(this->x - right.x, this->y - right.y, this->z - right.z);
    }

    vec3<T> operator-() const { return vec3<T>(-this->x, -this->y, -this->z); }

    vec3<T> operator*(T s) const {
        return vec3<T>(this->x * s, this->y * s, this->z * s);
    }

    void operator*=(T scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
    }

    void operator+=(vec3<T> right) {
        this->x += right.x;
        this->y += right.y;
        this->z += right.z;
    }

    void operator-=(vec3<T> right) {
        this->x -= right.x;
        this->y -= right.y;
        this->z -= right.z;
    }

    static T dot(const vec3<T> v1, const vec3<T> v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    T length() { return sqrt(x * x + y * y + z * z); }

    T squareLength() { return x * x + y * y + z * z; }

    void normalize() {
        T l = this->length();
        if (l > 1) {
            this->x *= ((T) 1 / l);
            this->y *= ((T) 1 / l);
            this->z *= ((T) 1 / l);
        }
    }

    void addScaledVector(float scale, const vec3<T>& vector) {
        this->x += scale * vector.x;
        this->y += scale * vector.y;
        this->z += scale * vector.z;
    }

    static vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2) {
        vec3<T> r;
        r.x = v1.y * v2.z - v1.z * v2.y;
        r.y = -(v1.x * v2.z - v1.z * v2.x);
        r.z = v1.x * v2.y - v1.y * v2.x;
        return r;
    }
};

template<typename T>
vec3<T> operator*(int s, vec3<T> v) {
    return vec3<T>(v.x * s, v.y * s, v.z * s);
}

template<typename T>
vec3<T> operator*(float s, vec3<T> v) {
    return vec3<T>(v.x * s, v.y * s, v.z * s);
}

template<typename T>
vec3<T> operator*(double s, vec3<T> v) {
    return vec3<T>(v.x * s, v.y * s, v.z * s);
}

template<typename T>
vec3<T> operator*(vec3<T> v, int s) {
    return vec3<T>(v.x * s, v.y * s, v.z * s);
}

template<typename T>
vec3<T> operator*(vec3<T> v, float s) {
    return vec3<T>(v.x * s, v.y * s, v.z * s);
}

template<typename T>
vec3<T> operator*(vec3<T> v, double s) {
    return vec3<T>(v.x * s, v.y * s, v.z * s);
}

typedef vec3<int> vec3i;
typedef vec3<float> vec3f;
typedef vec3<double> vec3d;

}  // namespace ta

#endif  // FOOBAR_VEC2_HPP
