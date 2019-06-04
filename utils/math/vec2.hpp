#ifndef FOOBAR_VEC2_HPP
#define FOOBAR_VEC2_HPP

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

#endif //FOOBAR_VEC2_HPP
