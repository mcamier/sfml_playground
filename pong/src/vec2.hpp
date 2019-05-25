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

    void invert()
    {
        x = -x;
        y = -y;
    }

    double magnitude()
    {
        return sqrt(x*x+y*y);
    }

    double squareMagnitude()
    {
        return x*x+y*y;
    }

    void normalize() {
        double magnitude = this->magnitude();

        if(magnitude > 1) {
            this->x *= ((double)1/magnitude);
            this->y *= ((double)1/magnitude);
        }
    }

    void translate(mat3& m) {
    }

    static vec2 multiply(vec2 source, double scalar)
    {
        return vec2(source.x*scalar, source.y*scalar);
    }



};

#endif //FOOBAR_VEC2_HPP
