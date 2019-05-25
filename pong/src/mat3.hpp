#ifndef FOOBAR_MAT3_HPP
#define FOOBAR_MAT3_HPP

struct mat3 {

public:
    float m00; float m01; float m02;
    float m10; float m11; float m12;
    float m20; float m21; float m22;

    mat3() {
        this->identity();
    }

    void identity() {
        m00 = 1; m01 = 0; m02 = 0;
        m10 = 0; m11 = 1; m12 = 0;
        m20 = 0; m21 = 0; m22 = 1;
    }

};

#endif //FOOBAR_MAT3_HPP
