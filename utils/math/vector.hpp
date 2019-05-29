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

    vec2(vec2& vec)
            :x(vec.x), y(vec.y) { }

    void invert()
    {
        x = -x;
        y = -y;
    }

    void scale(T value)
    {
        this->x *= value;
        this->y *= value;
    }

    double magnitude()
    {
        return sqrt(x*x+y*y);
    }

    double squareMagnitude()
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

    static vec2<T> multiply(vec2<T> source, T scalar)
    {
        return vec2(source.x*scalar, source.y*scalar);
    }
};

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

    vec3(vec3& vec)
            :x(vec.x), y(vec.y), z(vec.z) { }

    void invert()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    void scale(T value)
    {
        this->x *= value;
        this->y *= value;
        this->z *= value;
    }

    double magnitude()
    {
        return sqrt(x*x+y*y+z*z);
    }

    double squareMagnitude()
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

    static vec3<T> multiply(vec3<T> source, T scalar)
    {
        return vec2(source.x*scalar, source.y*scalar, source.z*scalar);
    }
};

typedef vec2<int> vec2i;
typedef vec2<float> vec2f;
typedef vec2<double> vec2d;

typedef vec3<int> vec3i;
typedef vec3<float> vec3f;
typedef vec3<double> vec3d;

#endif //FOOBAR_VECTOR_HPP
