#ifndef FOOBAR_VEC2_HPP
#define FOOBAR_VEC2_HPP

struct vec2 {

public:
    double x;

    double y;

    vec2()
            :x(0), y(0) { }

    vec2(double x, double y)
            :x(x), y(y) { }

    vec2(vec2& vec)
            :x(vec.x), y(vec.y) { }

    void invert();

    void scale(float value);

    double magnitude();

    double squareMagnitude();

    void normalize();

    static vec2 multiply(vec2 source, double scalar);

};

#endif //FOOBAR_VEC2_HPP
