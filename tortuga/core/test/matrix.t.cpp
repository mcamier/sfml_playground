#include "gtest/gtest.h"
#include "../include/tortuga/math/matrix.hpp"

using namespace std;
using namespace ta::core;

TEST(mat3, newMatrixShouldBeFilledWithZeros) {
    mat3 m;

    for(int i = 0 ; i < 9; i++) {
        EXPECT_EQ(m[i], 0);
    }
}

TEST(mat3, setIdentity) {
    mat3 m;
    m.resetAsIdentity();

    for(int i = 0 ; i < 9; i++) {
        if( i == 0  || i == 4 || i==8) {
            EXPECT_EQ(m[i], 1);
        }
        else {
            EXPECT_EQ(m[i], 0);
        }
    }
}

TEST(mat3, transpose) {
    mat3 m = mat3(  1.f,2.f,3.f,
                    4.f,5.f,6.f,
                    7.f,8.f, 9.f);
    m = m.transpose();

    EXPECT_EQ(m[0], 1.f);
    EXPECT_EQ(m[1], 4.f);
    EXPECT_EQ(m[2], 7.f);
    EXPECT_EQ(m[4], 5.f);
    EXPECT_EQ(m[5], 8.f);
    EXPECT_EQ(m[6], 3.f);
    EXPECT_EQ(m[7], 6.f);
    EXPECT_EQ(m[8], 9.f);
}

TEST(mat3, setTransposeOf) {
    mat3 n = mat3::identity();
    mat3 m = mat3(  1.f,2.f,3.f,
                    4.f,5.f,6.f,
                    7.f,8.f, 9.f);
    n.setTransposeOf(m);

    EXPECT_EQ(n[0], 1.f);
    EXPECT_EQ(n[1], 4.f);
    EXPECT_EQ(n[2], 7.f);
    EXPECT_EQ(n[3], 2.f);
    EXPECT_EQ(n[4], 5.f);
    EXPECT_EQ(n[5], 8.f);
    EXPECT_EQ(n[6], 3.f);
    EXPECT_EQ(n[7], 6.f);
    EXPECT_EQ(n[8], 9.f);
}

TEST(mat3, getDeterminantOfIdentityMatrix) {
    mat3 n = mat3::identity();
    float det = n.getDeterminant();

    EXPECT_EQ(det, 1.f);
}

TEST(mat3, getDeterminantOfMatrix) {
    mat3 m = mat3(  23.f,22.f,13.f,
                    94.f,15.f,66.f,
                    79.f,82.f, 19.f);
    float det = m.getDeterminant();

    EXPECT_EQ(det, 42294.f);
}

TEST(mat3, multiplyMatrices) {
    mat3 m = mat3(  1.f,2.f,3.f,
                    4.f,5.f,6.f,
                    7.f,8.f, 9.f);

    mat3 result = m * mat3::identity();
    EXPECT_EQ(result[0], 1.f);
    EXPECT_EQ(result[1], 2.f);
    EXPECT_EQ(result[2], 3.f);
    EXPECT_EQ(result[3], 4.f);
    EXPECT_EQ(result[4], 5.f);
    EXPECT_EQ(result[5], 6.f);
    EXPECT_EQ(result[6], 7.f);
    EXPECT_EQ(result[7], 8.f);
    EXPECT_EQ(result[8], 9.f);
}

TEST(mat3, inPlaceMultiplyMatrices) {
    mat3 result = mat3(  1.f,2.f,3.f,
                    4.f,5.f,6.f,
                    7.f,8.f, 9.f);

    result *= mat3::identity();
    EXPECT_EQ(result[0], 1.f);
    EXPECT_EQ(result[1], 2.f);
    EXPECT_EQ(result[2], 3.f);
    EXPECT_EQ(result[3], 4.f);
    EXPECT_EQ(result[4], 5.f);
    EXPECT_EQ(result[5], 6.f);
    EXPECT_EQ(result[6], 7.f);
    EXPECT_EQ(result[7], 8.f);
    EXPECT_EQ(result[8], 9.f);
}

TEST(mat3, inverse) {
    mat3 m = mat3(  1.f,2.f,3.f,
                    2.f,5.f,4.f,
                    3.f,4.f, 9.f);
    mat3 inv = m.inverse();

    EXPECT_EQ(inv[0], -7.25f);
    EXPECT_EQ(inv[1], 1.5f);
    EXPECT_EQ(inv[2], 1.75f);
    EXPECT_EQ(inv[3], 1.5f);
    EXPECT_EQ(inv[4], 0.f);
    EXPECT_EQ(inv[5], -0.5f);
    EXPECT_EQ(inv[6], 1.75f);
    EXPECT_EQ(inv[7], -0.5f);
    EXPECT_EQ(inv[8], -0.25f);
}

TEST(mat3, multiplyMatrixByItsInverseMustBeIdentity) {
    mat3 m = mat3(  1.f,2.f,3.f,
                    2.f,5.f,4.f,
                    3.f,4.f, 9.f);
    mat3 inv = m.inverse();

    mat3 result = m * inv;

    EXPECT_EQ(result[0], 1.f);
    EXPECT_EQ(result[1], 0.f);
    EXPECT_EQ(result[2], 0.f);
    EXPECT_EQ(result[3], 0.f);
    EXPECT_EQ(result[4], 1.f);
    EXPECT_EQ(result[5], 0.f);
    EXPECT_EQ(result[6], 0.f);
    EXPECT_EQ(result[7], 0.f);
    EXPECT_EQ(result[8], 1.f);
}




TEST(mat4, newMatrixShouldBeFilledWithZeros) {
    mat4 m;

    for(int i = 0 ; i < 16; i++) {
        EXPECT_EQ(m[i], 0);
    }
}

TEST(mat4, setIdentity) {
    mat4 m;
    m.resetAsIdentity();

    for(int i = 0 ; i < 16; i++) {
        if( i == 0  || i == 5 || i==10 || i == 15) {
            EXPECT_EQ(m[i], 1);
        }
        else {
            EXPECT_EQ(m[i], 0);
        }
    }
}


TEST(mat4, transpose) {
    mat4 m = mat4(  1.f,2.f,3.f,4.f,
                    5.f,6.f,7.f,8.f,
                    9.f,10.f, 11.f, 12.f,
                    13.f,14.f, 15.f, 16.f);
    m = m.transpose();

    EXPECT_EQ(m[0], 1.f);
    EXPECT_EQ(m[1], 5.f);
    EXPECT_EQ(m[2], 9.f);
    EXPECT_EQ(m[3], 13.f);
    EXPECT_EQ(m[4], 2.f);
    EXPECT_EQ(m[5], 6.f);
    EXPECT_EQ(m[6], 10.f);
    EXPECT_EQ(m[7], 14.f);
    EXPECT_EQ(m[8], 3.f);
    EXPECT_EQ(m[9], 7.f);
    EXPECT_EQ(m[10], 11.f);
    EXPECT_EQ(m[11], 15.f);
    EXPECT_EQ(m[12], 4.f);
    EXPECT_EQ(m[13], 8.f);
    EXPECT_EQ(m[14], 12.f);
    EXPECT_EQ(m[15], 16.f);
}

TEST(mat4, setTransposeOf) {
    mat4 n = mat4::identity();
    mat4 m = mat4(  1.f,2.f,3.f,4.f,
                    5.f,6.f,7.f,8.f,
                    9.f,10.f, 11.f, 12.f,
                    13.f,14.f, 15.f, 16.f);
    n.setTransposeOf(m);

    EXPECT_EQ(n[0], 1.f);
    EXPECT_EQ(n[1], 5.f);
    EXPECT_EQ(n[2], 9.f);
    EXPECT_EQ(n[3], 13.f);
    EXPECT_EQ(n[4], 2.f);
    EXPECT_EQ(n[5], 6.f);
    EXPECT_EQ(n[6], 10.f);
    EXPECT_EQ(n[7], 14.f);
    EXPECT_EQ(n[8], 3.f);
    EXPECT_EQ(n[9], 7.f);
    EXPECT_EQ(n[10], 11.f);
    EXPECT_EQ(n[11], 15.f);
    EXPECT_EQ(n[12], 4.f);
    EXPECT_EQ(n[13], 8.f);
    EXPECT_EQ(n[14], 12.f);
    EXPECT_EQ(n[15], 16.f);
}

TEST(mat4, getDeterminantOfIdentityMatrix) {
    mat4 n = mat4::identity();
    float det = n.getDeterminant();

    EXPECT_EQ(det, 1.f);
}

TEST(mat4, getDeterminantOfMatrix) {
    mat4 m = mat4(  23.f,22.f,13.f,23.f,
                    94.f,15.f, 66.f,94.f,
                    4.f,5.f, 6.f,4.f,
                    79.f,82.f, 19.f, 79.f);
    float det = m.getDeterminant();

    EXPECT_EQ(det, -35770.f);
}

TEST(mat4, multiplyMatrices) {
    mat4 m = mat4(  1.f,2.f,3.f,4.f,
                    5.f,6.f,7.f,8.f,
                    9.f,10.f,11.f,12.f,
                    13.f,14.f, 15.f, 16.f);

    mat4 result = m * mat4::identity();
    for(int i = 0 ; i < 16; i++) {
        EXPECT_EQ(result[i], i+1);
    }
}

TEST(mat4, multiplyMatrixByItsInverseMustBeIdentity) {
    mat4 m = mat4::identity();
    mat4 inv = m.inverse();

    mat4 result = m * inv;

    EXPECT_EQ(result[0], 1.f);
    EXPECT_EQ(result[1], 0.f);
    EXPECT_EQ(result[2], 0.f);
    EXPECT_EQ(result[3], 0.f);
    EXPECT_EQ(result[4], 1.f);
    EXPECT_EQ(result[5], 0.f);
    EXPECT_EQ(result[6], 0.f);
    EXPECT_EQ(result[7], 0.f);
    EXPECT_EQ(result[8], 1.f);
}

TEST(mat4, inPlaceMultiplyMatrices) {
    mat4 result = mat4(  1.f, 2.f, 3.f, 4.f,
                         5.f, 6.f, 7.f, 8.f,
                         9.f, 10.f, 11.f, 12.f,
                         13.f, 14.f, 15.f, 16.f);

    result *= mat4::identity();
    for(int i = 0 ; i < 16; i++) {
        EXPECT_EQ(result[i], i+1);
    }
}

TEST(mat4, inverse) {
    // TODO
    //mat4 m = mat4(  1.f,2.f,3.f,
    //                2.f,5.f,4.f,
    //                3.f,4.f, 9.f);
    //mat4 inv = m.inverse();
//
    //EXPECT_EQ(inv[0], -7.25f);
    //EXPECT_EQ(inv[1], 1.5f);
    //EXPECT_EQ(inv[2], 1.75f);
    //EXPECT_EQ(inv[3], 1.5f);
    //EXPECT_EQ(inv[4], 0.f);
    //EXPECT_EQ(inv[5], -0.5f);
    //EXPECT_EQ(inv[6], 1.75f);
    //EXPECT_EQ(inv[7], -0.5f);
    //EXPECT_EQ(inv[8], -0.25f);
}