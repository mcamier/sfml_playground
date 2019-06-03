#ifndef FOOBAR_VECTOR_HPP
#define FOOBAR_VECTOR_HPP

template<typename T>
class vec2 {
public:
    T x;
    T y;

    vec2()
            :x(0), y(0) { }

    vec2(T x, T y)
            :x(x), y(y) { }

    vec2(const vec2& vec)
            :x(vec.x), y(vec.y) { }

    vec2<T> operator+(const vec2<T>& right) const {
        return vec2<T>(this->x + right.x, this->y + right.y);
    } 

    vec2<T> operator-(const vec2<T>& right) const {
        return vec2<T>(this->x - right.x, this->y - right.y);
    } 

    vec2<T> operator-() const {
        return vec2<T>(-this->x, -this->y);
    } 

    static T dot(const vec2<T> v1, const vec2<T> v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    double length()
    {
        return sqrt(x*x+y*y);
    }

    double squareLength()
    {
        return x*x+y*y;
    }

    void normalize()
    {
        double magnitude = this->magnitude();

        if (magnitude>1) {
            this->x *= ((double) 1/magnitude);
            this->y *= ((double) 1/magnitude);
        }
    }
};

template<typename T>
vec2<T> operator*(int s, vec2<T> v) {
    return vec2<T>(v.x * s, v.y * s);
} 

template<typename T>
vec2<T> operator*(float s, vec2<T> v) {
    return vec2<T>(v.x * s, v.y * s);
} 

template<typename T>
vec2<T> operator*(double s, vec2<T> v) {
    return vec2<T>(v.x * s, v.y * s);
} 

template<typename T>
vec2<T> operator*(vec2<T> v, int s) {
    return vec2<T>(v.x * s, v.y * s);
} 

template<typename T>
vec2<T> operator*(vec2<T> v, float s) {
    return vec2<T>(v.x * s, v.y * s);
} 

template<typename T>
vec2<T> operator*(vec2<T> v, double s) {
    return vec2<T>(v.x * s, v.y * s);
} 

typedef vec2<int> vec2i;
typedef vec2<float> vec2f;
typedef vec2<double> vec2d;


template<typename T>
class vec3 {
public:
    T x;
    T y;
    T z;

    vec3()
            :x(0), y(0), z(0) { }

    vec3(T x, T y, T z)
            :x(x), y(y), z(z) { }

    vec3(const vec3& vec)
            :x(vec.x), y(vec.y), z(vec.z) { }

    vec3<T> operator+(const vec3<T>& right) const {
        return vec3<T>(this->x + right.x, this->y + right.y, this->z + right.z);
    } 

    vec3<T> operator-(const vec3<T>& right) const {
        return vec3<T>(this->x - right.x, this->y - right.y, this->z - right.z);
    } 

    vec3<T> operator-() const {
        return vec3<T>(-this->x, -this->y, -this->z);
    } 

    vec3<T> operator*(T s) const {
        return vec3<T>(this->x * s, this->y * s, this->z * s);
    } 

    static T dot(const vec3<T> v1, const vec3<T> v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    double length()
    {
        return sqrt(x*x+y*y+z*z);
    }

    double squareLength()
    {
        return x*x+y*y+z*z;
    }

    void normalize()
    {
        double magnitude = this->magnitude();

        if (magnitude>1) {
            this->x *= ((double) 1/magnitude);
            this->y *= ((double) 1/magnitude);
            this->z *= ((double) 1/magnitude);
        }
    }

    static vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2) {
        vec3<T> r;
        r.x = v1.y*v2.z-v1.z*v2.y;
        r.y = -(v1.x*v2.z-v1.z*v2.x);
        r.z = v1.x*v2.y-v1.y*v2.x;
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

#endif //FOOBAR_VECTOR_HPP
