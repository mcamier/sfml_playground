#ifndef TORTUGA_MATRIX_HPP
#define TORTUGA_MATRIX_HPP

#include "vector.hpp"

namespace ta::core {

/**
 * 3x3 row major matrix with float precision
 */
class mat3 {
    float data[9];

public:
    mat3() {
        for(int i = 0 ; i < 9 ; i++) {
            data[i] = 0;
        }
    }

    mat3( float a, float b, float c,
                float d, float e, float f,
                float g, float h, float i) {
        data[0] = a; data[1] = b; data[2] = c;
        data[3] = d; data[4] = e; data[5] = f;
        data[6] = g; data[7] = h; data[8] = i;
    }

    /**
     * Get a new identity matrix
     *
     * @return a new identity matrix
     */
    static mat3 identity() {
        mat3 identity;
        identity.data[0] = 1;
        identity.data[4] = 1;
        identity.data[8] = 1;
        return identity;
    }

    /**
     * Reset the instance of matrix an identity matrix
     */
    void resetAsIdentity() {
        for(int i = 0 ; i < 9 ; i++) {
            if(i == 0 || (i % 4 == 0)) {
                data[i] = 1;
            } else {
                data[i] = 0;
            }
        }
    }

    /**
     * Return the determinant of the instance of matrix
     *
     * @return determinant as a scalar value
     */
    float getDeterminant() const {
        return   data[0] * data[4] * data[8] +
                 data[3] * data[7] * data[2] +
                 data[6] * data[1] * data[5] -
                 data[0] * data[7] * data[5] -
                 data[6] * data[4] * data[2] -
                 data[3] * data[1] * data[8];
    }

    /**
     * Get a new matrix containing the transpose of the instance matrix
     *
     * @return transpose matrix
     */
    mat3 transpose() const {
        mat3 result;
        result.setTransposeOf(*this);
        return result;
    }

    /**
     * Make the instance of matrix the transponse of the provided matrix
     * @param other
     */
    void setTransposeOf(const mat3& other) {
        data[0] = other.data[0]; data[1] = other.data[3]; data[2] = other.data[6];
        data[3] = other.data[1]; data[4] = other.data[4]; data[5] = other.data[7];
        data[6] = other.data[2]; data[7] = other.data[5]; data[8] = other.data[8];
    }

    /**
     * Get a new matrix containing the inverse of the instance matrix
     * The inverse matrix undoes the effect of the original matrix
     *
     * @return inverse matrix
     */
    mat3 inverse() const {
        mat3 result;
        result.setInverseOf(*this);
        return result;
    }

    /**
     * Make the instance of matrix the inverse of the provided matrix
     * @param other
     */
    void setInverseOf(const mat3& o) {
        float det = o.getDeterminant();
        if(det == 0.0) return;
        float invDet = 1.0 / det;

        data[0] = (o[4]*o[8]-o[5]*o[7]) * invDet;
        data[1] = (o[2]*o[7]-o[1]*o[8]) * invDet;
        data[2] = (o[1]*o[5]-o[2]*o[4]) * invDet;
        data[3] = (o[5]*o[6]-o[3]*o[8]) * invDet;
        data[4] = (o[0]*o[8]-o[2]*o[6]) * invDet;
        data[5] = (o[2]*o[3]-o[0]*o[5]) * invDet;
        data[6] = (o[3]*o[7]-o[4]*o[6]) * invDet;
        data[7] = (o[1]*o[6]-o[0]*o[7]) * invDet;
        data[8] = (o[0]*o[4]-o[1]*o[3]) * invDet;
    }

    const float& operator[](std::size_t idx) const {
        return data[idx];
    }

    mat3 operator*(const mat3& rhs) const {
        return mat3(
                data[0]*rhs[0] + data[1]*rhs[3] + data[2]*rhs[6],
                data[0]*rhs[1] + data[1]*rhs[4] + data[2]*rhs[7],
                data[0]*rhs[2] + data[1]*rhs[5] + data[2]*rhs[8],

                data[3]*rhs[0] + data[4]*rhs[3] + data[5]*rhs[6],
                data[3]*rhs[1] + data[4]*rhs[4] + data[5]*rhs[7],
                data[3]*rhs[2] + data[4]*rhs[5] + data[5]*rhs[8],

                data[6]*rhs[0] + data[7]*rhs[3] + data[8]*rhs[6],
                data[6]*rhs[1] + data[7]*rhs[4] + data[8]*rhs[7],
                data[6]*rhs[2] + data[7]*rhs[5] + data[8]*rhs[8]
        );
    }

    void operator*=(const mat3& rhs) {
        float t1, t2, t3;
        t1 = data[0]*rhs[0] + data[1]*rhs[3] + data[2]*rhs[6];
        t2 = data[0]*rhs[1] + data[1]*rhs[4] + data[2]*rhs[7];
        t3 = data[0]*rhs[2] + data[1]*rhs[5] + data[2]*rhs[8];
        data[0] = t1;
        data[1] = t2;
        data[2] = t3;

        t1 = data[3]*rhs[0] + data[4]*rhs[3] + data[5]*rhs[6];
        t2 = data[3]*rhs[1] + data[4]*rhs[4] + data[5]*rhs[7];
        t3 = data[3]*rhs[2] + data[4]*rhs[5] + data[5]*rhs[8];
        data[3] = t1;
        data[4] = t2;
        data[5] = t3;

        t1 = data[6]*rhs[0] + data[7]*rhs[3] + data[8]*rhs[6];
        t2 = data[6]*rhs[1] + data[7]*rhs[4] + data[8]*rhs[7];
        t3 = data[6]*rhs[2] + data[7]*rhs[5] + data[8]*rhs[8];
        data[6] = t1;
        data[7] = t2;
        data[8] = t3;
    }
};

/**
 * 4x4 row major matrix with float precision
 */
class mat4 {
    float data[16];

public:
    mat4() {
        for(int i = 0 ; i < 16 ; i++) {
            data[i] = 0;
        }
    }

    mat4(float a, float b, float c, float d,
         float e, float f, float g, float h,
         float i, float j, float k, float l,
         float m, float n, float o, float p) {
        data[0] = a;  data[1] = b;  data[2] = c;  data[3] = d;
        data[4] = e;  data[5] = f;  data[6] = g;  data[7] = h;
        data[8] = i;  data[9] = j;  data[10] = k; data[11] = l;
        data[12] = m; data[13] = n; data[14] = o; data[15] = p;
    }

    /**
     * Return an new identity matrix
     * @return
     */
    static mat4 identity() {
        mat4 identity;
        identity.data[0] = 1;
        identity.data[5] = 1;
        identity.data[10] = 1;
        identity.data[15] = 1;
        return identity;
    }

    /**
     * Set the instance as a identity matrix
     */
    void resetAsIdentity() {
        for(int i = 0 ; i < 16 ; i++) {
            if(i == 0 || (i % 5 == 0)) {
                data[i] = 1;
            } else {
                data[i] = 0;
            }
        }
    }

    /**
     * Return the determinant of the instance of matrix
     *
     * @return determinant as a scalar value
     */
    float getDeterminant() const {
        // todo
        return  0;
    }

    /**
     * Get a new matrix containing the inverse of the instance matrix
     * The inverse matrix undoes the effect of the original matrix
     *
     * @return inverse matrix
     */
    mat4 inverse() const {
        mat4 result;
        result.setInverseOf(*this);
        return result;
    }

    /**
     * Make the instance of matrix the inverse of the provided matrix
     * @param other
     */
    void setInverseOf(const mat4& o) {
        float det = o.getDeterminant();
        if(det == 0.0) return;
        float invDet = 1.0 / det;

        // todo
    }

    /**
     * Get a new matrix containing the transpose of the instance matrix
     *
     * @return transpose matrix
     */
    mat4 transpose() {
        mat4 result;
        result.setTransposeOf(*this);
        return result;
    }

    /**
     * Make the instance of matrix the transponse of the provided matrix
     * @param other
     */
    void setTransposeOf(const mat4& other) {
        data[0] = other.data[0];  data[1] = other.data[4];  data[2] = other.data[8];  data[3] = other.data[12];
        data[4] = other.data[1];  data[5] = other.data[5];  data[6] = other.data[9];  data[7] = other.data[13];
        data[8] = other.data[2];  data[9] = other.data[6];  data[10] = other.data[10]; data[11] = other.data[14];
        data[12] = other.data[3]; data[13] = other.data[7]; data[14] = other.data[11]; data[15] = other.data[15];
    }

    const float& operator[](std::size_t idx) const {
        return data[idx];
    }

    mat4 operator*(const mat4& rhs) const {
        return mat4(
                data[0]*rhs[0] + data[1]*rhs[4] + data[2]*rhs[8] + data[3]*rhs[12],
                data[0]*rhs[1] + data[1]*rhs[5] + data[2]*rhs[9] + data[3]*rhs[13],
                data[0]*rhs[2] + data[1]*rhs[6] + data[2]*rhs[10] + data[3]*rhs[14],
                data[0]*rhs[3] + data[1]*rhs[7] + data[2]*rhs[11] + data[3]*rhs[15],

                data[4]*rhs[0] + data[5]*rhs[4] + data[6]*rhs[8] + data[7]*rhs[12],
                data[4]*rhs[1] + data[5]*rhs[5] + data[6]*rhs[9] + data[7]*rhs[13],
                data[4]*rhs[2] + data[5]*rhs[6] + data[6]*rhs[10] + data[7]*rhs[14],
                data[4]*rhs[3] + data[5]*rhs[7] + data[6]*rhs[11] + data[7]*rhs[15],

                data[8]*rhs[0] + data[9]*rhs[4] + data[10]*rhs[8] + data[11]*rhs[12],
                data[8]*rhs[1] + data[9]*rhs[5] + data[10]*rhs[9] + data[11]*rhs[13],
                data[8]*rhs[2] + data[9]*rhs[6] + data[10]*rhs[10] + data[11]*rhs[14],
                data[8]*rhs[3] + data[9]*rhs[7] + data[10]*rhs[11] + data[11]*rhs[15],

                data[12]*rhs[0] + data[13]*rhs[4] + data[14]*rhs[8] + data[15]*rhs[12],
                data[12]*rhs[1] + data[13]*rhs[5] + data[14]*rhs[9] + data[15]*rhs[13],
                data[12]*rhs[2] + data[13]*rhs[6] + data[14]*rhs[10] + data[15]*rhs[14],
                data[12]*rhs[3] + data[13]*rhs[7] + data[14]*rhs[11] + data[15]*rhs[15]
        );
    }

    void operator*=(const mat4& rhs) {
        float t1, t2, t3, t4;

        t1 = data[0]*rhs[0] + data[1]*rhs[4] + data[2]*rhs[8] + data[3]*rhs[12];
        t2 = data[0]*rhs[1] + data[1]*rhs[5] + data[2]*rhs[9] + data[3]*rhs[13];
        t3 = data[0]*rhs[2] + data[1]*rhs[6] + data[2]*rhs[10] + data[3]*rhs[14];
        t4 = data[0]*rhs[3] + data[1]*rhs[7] + data[2]*rhs[11] + data[3]*rhs[15];
        data[0] = t1;
        data[1] = t2;
        data[2] = t3;
        data[3] = t4;

        t1 = data[4]*rhs[0] + data[5]*rhs[4] + data[6]*rhs[8] + data[7]*rhs[12];
        t2 = data[4]*rhs[1] + data[5]*rhs[5] + data[6]*rhs[9] + data[7]*rhs[13];
        t3 = data[4]*rhs[2] + data[5]*rhs[6] + data[6]*rhs[10] + data[7]*rhs[14];
        t4 = data[4]*rhs[3] + data[5]*rhs[7] + data[6]*rhs[11] + data[7]*rhs[15];
        data[4] = t1;
        data[5] = t2;
        data[6] = t3;
        data[7] = t4;

        t1 = data[8]*rhs[0] + data[9]*rhs[4] + data[10]*rhs[8] + data[11]*rhs[12];
        t2 = data[8]*rhs[1] + data[9]*rhs[5] + data[10]*rhs[9] + data[11]*rhs[13];
        t3 = data[8]*rhs[2] + data[9]*rhs[6] + data[10]*rhs[10] + data[11]*rhs[14];
        t4 = data[8]*rhs[3] + data[9]*rhs[7] + data[10]*rhs[11] + data[11]*rhs[15];
        data[8] = t1;
        data[9] = t2;
        data[10] = t3;
        data[11] = t4;

        t1 = data[12]*rhs[0] + data[13]*rhs[4] + data[14]*rhs[8] + data[15]*rhs[12];
        t2 = data[12]*rhs[1] + data[13]*rhs[5] + data[14]*rhs[9] + data[15]*rhs[13];
        t3 = data[12]*rhs[2] + data[13]*rhs[6] + data[14]*rhs[10] + data[15]*rhs[14];
        t4 = data[12]*rhs[3] + data[13]*rhs[7] + data[14]*rhs[11] + data[15]*rhs[15];
        data[12] = t1;
        data[13] = t2;
        data[14] = t3;
        data[15] = t4;
    }
};

}

#endif //TORTUGAX_MATRIX_HPP
