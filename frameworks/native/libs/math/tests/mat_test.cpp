/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "MatTest"

#include <stdlib.h>

#include <limits>
#include <random>
#include <functional>

#include <gtest/gtest.h>

#include <math/mat2.h>
#include <math/mat4.h>

namespace android {

class MatTest : public testing::Test {
protected:
};

TEST_F(MatTest, Basics) {
    mat4 m0;
    EXPECT_EQ(sizeof(m0), sizeof(float)*16);
}

TEST_F(MatTest, ComparisonOps) {
    mat4 m0;
    mat4 m1(2);

    EXPECT_TRUE(m0 == m0);
    EXPECT_TRUE(m0 != m1);
    EXPECT_FALSE(m0 != m0);
    EXPECT_FALSE(m0 == m1);
}

TEST_F(MatTest, Constructors) {
    mat4 m0;
    ASSERT_EQ(m0[0].x, 1);
    ASSERT_EQ(m0[0].y, 0);
    ASSERT_EQ(m0[0].z, 0);
    ASSERT_EQ(m0[0].w, 0);
    ASSERT_EQ(m0[1].x, 0);
    ASSERT_EQ(m0[1].y, 1);
    ASSERT_EQ(m0[1].z, 0);
    ASSERT_EQ(m0[1].w, 0);
    ASSERT_EQ(m0[2].x, 0);
    ASSERT_EQ(m0[2].y, 0);
    ASSERT_EQ(m0[2].z, 1);
    ASSERT_EQ(m0[2].w, 0);
    ASSERT_EQ(m0[3].x, 0);
    ASSERT_EQ(m0[3].y, 0);
    ASSERT_EQ(m0[3].z, 0);
    ASSERT_EQ(m0[3].w, 1);

    mat4 m1(2);
    mat4 m2(vec4(2));
    mat4 m3(m2);

    EXPECT_EQ(m1, m2);
    EXPECT_EQ(m2, m3);
    EXPECT_EQ(m3, m1);

    mat4 m4(vec4(1), vec4(2), vec4(3), vec4(4));
    EXPECT_NE(m4, m1);
}

TEST_F(MatTest, ArithmeticOps) {
    mat4 m0;
    mat4 m1(2);
    mat4 m2(vec4(2));

    m1 += m2;
    EXPECT_EQ(mat4(4), m1);

    m2 -= m1;
    EXPECT_EQ(mat4(-2), m2);

    m1 *= 2;
    EXPECT_EQ(mat4(8), m1);

    m1 /= 2;
    EXPECT_EQ(mat4(4), m1);

    m0 = -m0;
    EXPECT_EQ(mat4(-1), m0);
}

TEST_F(MatTest, UnaryOps) {
    const mat4 identity;
    mat4 m0;

    m0 = -m0;
    EXPECT_EQ(mat4(vec4(-1, 0,  0,  0),
                   vec4(0, -1,  0,  0),
                   vec4(0,  0, -1,  0),
                   vec4(0,  0,  0, -1)), m0);

    m0 = -m0;
    EXPECT_EQ(identity, m0);
}

TEST_F(MatTest, MiscOps) {
    const mat4 identity;
    mat4 m0;
    EXPECT_EQ(4, trace(m0));

    mat4 m1(vec4(1, 2, 3, 4), vec4(5, 6, 7, 8), vec4(9, 10, 11, 12), vec4(13, 14, 15, 16));
    mat4 m2(vec4(1, 5, 9, 13), vec4(2, 6, 10, 14), vec4(3, 7, 11, 15), vec4(4, 8, 12, 16));
    EXPECT_EQ(m1, transpose(m2));
    EXPECT_EQ(m2, transpose(m1));
    EXPECT_EQ(vec4(1, 6, 11, 16), diag(m1));

    EXPECT_EQ(identity, inverse(identity));

    mat4 m3(vec4(4, 3, 0, 0), vec4(3, 2, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
    mat4 m3i(inverse(m3));
    EXPECT_FLOAT_EQ(-2, m3i[0][0]);
    EXPECT_FLOAT_EQ(3,  m3i[0][1]);
    EXPECT_FLOAT_EQ(3,  m3i[1][0]);
    EXPECT_FLOAT_EQ(-4, m3i[1][1]);

    mat4 m3ii(inverse(m3i));
    EXPECT_FLOAT_EQ(m3[0][0], m3ii[0][0]);
    EXPECT_FLOAT_EQ(m3[0][1], m3ii[0][1]);
    EXPECT_FLOAT_EQ(m3[1][0], m3ii[1][0]);
    EXPECT_FLOAT_EQ(m3[1][1], m3ii[1][1]);

    EXPECT_EQ(m1, m1*identity);


    for (size_t c=0 ; c<4 ; c++) {
        for (size_t r=0 ; r<4 ; r++) {
            EXPECT_FLOAT_EQ(m1[c][r], m1(r, c));
        }
    }
}

TEST_F(MatTest, ElementAccess) {
    mat4 m(vec4(1, 2, 3, 4), vec4(5, 6, 7, 8), vec4(9, 10, 11, 12), vec4(13, 14, 15, 16));
    for (size_t c=0 ; c<4 ; c++) {
        for (size_t r=0 ; r<4 ; r++) {
            EXPECT_FLOAT_EQ(m[c][r], m(r, c));
        }
    }

    m(3,2) = 100;
    EXPECT_FLOAT_EQ(m[2][3], 100);
    EXPECT_FLOAT_EQ(m(3, 2), 100);
}

//------------------------------------------------------------------------------
// MAT 3
//------------------------------------------------------------------------------

class Mat3Test : public testing::Test {
protected:
};

TEST_F(Mat3Test, Basics) {
    mat3 m0;
    EXPECT_EQ(sizeof(m0), sizeof(float)*9);
}

TEST_F(Mat3Test, ComparisonOps) {
    mat3 m0;
    mat3 m1(2);

    EXPECT_TRUE(m0 == m0);
    EXPECT_TRUE(m0 != m1);
    EXPECT_FALSE(m0 != m0);
    EXPECT_FALSE(m0 == m1);
}

TEST_F(Mat3Test, Constructors) {
    mat3 m0;
    ASSERT_EQ(m0[0].x, 1);
    ASSERT_EQ(m0[0].y, 0);
    ASSERT_EQ(m0[0].z, 0);
    ASSERT_EQ(m0[1].x, 0);
    ASSERT_EQ(m0[1].y, 1);
    ASSERT_EQ(m0[1].z, 0);
    ASSERT_EQ(m0[2].x, 0);
    ASSERT_EQ(m0[2].y, 0);
    ASSERT_EQ(m0[2].z, 1);

    mat3 m1(2);
    mat3 m2(vec3(2));
    mat3 m3(m2);

    EXPECT_EQ(m1, m2);
    EXPECT_EQ(m2, m3);
    EXPECT_EQ(m3, m1);
}

TEST_F(Mat3Test, ArithmeticOps) {
    mat3 m0;
    mat3 m1(2);
    mat3 m2(vec3(2));

    m1 += m2;
    EXPECT_EQ(mat3(4), m1);

    m2 -= m1;
    EXPECT_EQ(mat3(-2), m2);

    m1 *= 2;
    EXPECT_EQ(mat3(8), m1);

    m1 /= 2;
    EXPECT_EQ(mat3(4), m1);

    m0 = -m0;
    EXPECT_EQ(mat3(-1), m0);
}

TEST_F(Mat3Test, UnaryOps) {
    const mat3 identity;
    mat3 m0;

    m0 = -m0;
    EXPECT_EQ(mat3(vec3(-1, 0,  0),
                   vec3(0, -1,  0),
                   vec3(0,  0, -1)), m0);

    m0 = -m0;
    EXPECT_EQ(identity, m0);
}

TEST_F(Mat3Test, MiscOps) {
    const mat3 identity;
    mat3 m0;
    EXPECT_EQ(3, trace(m0));

    mat3 m1(vec3(1, 2, 3), vec3(4, 5, 6), vec3(7, 8, 9));
    mat3 m2(vec3(1, 4, 7), vec3(2, 5, 8), vec3(3, 6, 9));
    EXPECT_EQ(m1, transpose(m2));
    EXPECT_EQ(m2, transpose(m1));
    EXPECT_EQ(vec3(1, 5, 9), diag(m1));

    EXPECT_EQ(identity, inverse(identity));

    mat3 m3(vec3(4, 3, 0), vec3(3, 2, 0), vec3(0, 0, 1));
    mat3 m3i(inverse(m3));
    EXPECT_FLOAT_EQ(-2, m3i[0][0]);
    EXPECT_FLOAT_EQ(3,  m3i[0][1]);
    EXPECT_FLOAT_EQ(3,  m3i[1][0]);
    EXPECT_FLOAT_EQ(-4, m3i[1][1]);

    mat3 m3ii(inverse(m3i));
    EXPECT_FLOAT_EQ(m3[0][0], m3ii[0][0]);
    EXPECT_FLOAT_EQ(m3[0][1], m3ii[0][1]);
    EXPECT_FLOAT_EQ(m3[1][0], m3ii[1][0]);
    EXPECT_FLOAT_EQ(m3[1][1], m3ii[1][1]);

    EXPECT_EQ(m1, m1*identity);
}

//------------------------------------------------------------------------------
// MAT 2
//------------------------------------------------------------------------------

class Mat2Test : public testing::Test {
protected:
};

TEST_F(Mat2Test, Basics) {
    mat2 m0;
    EXPECT_EQ(sizeof(m0), sizeof(float)*4);
}

TEST_F(Mat2Test, ComparisonOps) {
    mat2 m0;
    mat2 m1(2);

    EXPECT_TRUE(m0 == m0);
    EXPECT_TRUE(m0 != m1);
    EXPECT_FALSE(m0 != m0);
    EXPECT_FALSE(m0 == m1);
}

TEST_F(Mat2Test, Constructors) {
    mat2 m0;
    ASSERT_EQ(m0[0].x, 1);
    ASSERT_EQ(m0[0].y, 0);
    ASSERT_EQ(m0[1].x, 0);
    ASSERT_EQ(m0[1].y, 1);

    mat2 m1(2);
    mat2 m2(vec2(2));
    mat2 m3(m2);

    EXPECT_EQ(m1, m2);
    EXPECT_EQ(m2, m3);
    EXPECT_EQ(m3, m1);
}

TEST_F(Mat2Test, ArithmeticOps) {
    mat2 m0;
    mat2 m1(2);
    mat2 m2(vec2(2));

    m1 += m2;
    EXPECT_EQ(mat2(4), m1);

    m2 -= m1;
    EXPECT_EQ(mat2(-2), m2);

    m1 *= 2;
    EXPECT_EQ(mat2(8), m1);

    m1 /= 2;
    EXPECT_EQ(mat2(4), m1);

    m0 = -m0;
    EXPECT_EQ(mat2(-1), m0);
}

TEST_F(Mat2Test, UnaryOps) {
    const mat2 identity;
    mat2 m0;

    m0 = -m0;
    EXPECT_EQ(mat2(vec2(-1, 0),
                   vec2(0, -1)), m0);

    m0 = -m0;
    EXPECT_EQ(identity, m0);
}

TEST_F(Mat2Test, MiscOps) {
    const mat2 identity;
    mat2 m0;
    EXPECT_EQ(2, trace(m0));

    mat2 m1(vec2(1, 2), vec2(3, 4));
    mat2 m2(vec2(1, 3), vec2(2, 4));
    EXPECT_EQ(m1, transpose(m2));
    EXPECT_EQ(m2, transpose(m1));
    EXPECT_EQ(vec2(1, 4), diag(m1));

    EXPECT_EQ(identity, inverse(identity));

    EXPECT_EQ(m1, m1*identity);
}

//------------------------------------------------------------------------------
// MORE MATRIX TESTS
//------------------------------------------------------------------------------

template <typename T>
class MatTestT : public ::testing::Test {
public:
};

typedef ::testing::Types<float,float> TestMatrixValueTypes;

TYPED_TEST_CASE(MatTestT, TestMatrixValueTypes);

#define TEST_MATRIX_INVERSE(MATRIX, EPSILON)                                \
{                                                                           \
    typedef decltype(MATRIX) MatrixType;                                    \
    MatrixType inv1 = inverse(MATRIX);                                      \
    MatrixType ident1 = MATRIX * inv1;                                      \
    static const MatrixType IDENTITY;                                       \
    for (size_t row = 0; row < MatrixType::ROW_SIZE; ++row) {               \
        for (size_t col = 0; col < MatrixType::COL_SIZE; ++col) {           \
            EXPECT_NEAR(ident1[row][col], IDENTITY[row][col], EPSILON);     \
        }                                                                   \
    }                                                                       \
}

TYPED_TEST(MatTestT, Inverse4) {
    typedef ::android::details::TMat44<TypeParam> M44T;

    M44T m1(1,  0,  0,  0,
            0,  1,  0,  0,
            0,  0,  1,  0,
            0,  0,  0,  1);

    M44T m2(0,  -1,  0,  0,
            1,  0,  0,  0,
            0,  0,  1,  0,
            0,  0,  0,  1);

    M44T m3(1,  0,  0,  0,
            0,  2,  0,  0,
            0,  0,  0,  1,
            0,  0,  -1,  0);

    M44T m4(
            4.683281e-01, 1.251189e-02, -8.834660e-01, -4.726541e+00,
             -8.749647e-01,  1.456563e-01, -4.617587e-01, 3.044795e+00,
             1.229049e-01,  9.892561e-01, 7.916244e-02, -6.737138e+00,
             0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00);

    M44T m5(
        4.683281e-01, 1.251189e-02, -8.834660e-01, -4.726541e+00,
        -8.749647e-01,  1.456563e-01, -4.617587e-01, 3.044795e+00,
        1.229049e-01,  9.892561e-01, 7.916244e-02, -6.737138e+00,
        1.000000e+00, 2.000000e+00, 3.000000e+00, 4.000000e+00);

    TEST_MATRIX_INVERSE(m1, 0);
    TEST_MATRIX_INVERSE(m2, 0);
    TEST_MATRIX_INVERSE(m3, 0);
    TEST_MATRIX_INVERSE(m4, 20.0 * std::numeric_limits<TypeParam>::epsilon());
    TEST_MATRIX_INVERSE(m5, 20.0 * std::numeric_limits<TypeParam>::epsilon());
}

//------------------------------------------------------------------------------
TYPED_TEST(MatTestT, Inverse3) {
    typedef ::android::details::TMat33<TypeParam> M33T;

    M33T m1(1,  0,  0,
            0,  1,  0,
            0,  0,  1);

    M33T m2(0,  -1,  0,
            1,  0,  0,
            0,  0,  1);

    M33T m3(2,  0,  0,
            0,  0,  1,
            0,  -1,  0);

    M33T m4(
            4.683281e-01, 1.251189e-02, 0.000000e+00,
            -8.749647e-01, 1.456563e-01, 0.000000e+00,
            0.000000e+00, 0.000000e+00, 1.000000e+00);

    M33T m5(
            4.683281e-01, 1.251189e-02, -8.834660e-01,
           -8.749647e-01, 1.456563e-01, -4.617587e-01,
            1.229049e-01, 9.892561e-01, 7.916244e-02);

    TEST_MATRIX_INVERSE(m1, 0);
    TEST_MATRIX_INVERSE(m2, 0);
    TEST_MATRIX_INVERSE(m3, 0);
    TEST_MATRIX_INVERSE(m4, 20.0 * std::numeric_limits<TypeParam>::epsilon());
    TEST_MATRIX_INVERSE(m5, 20.0 * std::numeric_limits<TypeParam>::epsilon());
}

//------------------------------------------------------------------------------
TYPED_TEST(MatTestT, Inverse2) {
    typedef ::android::details::TMat22<TypeParam> M22T;

    M22T m1(1,  0,
            0,  1);

    M22T m2(0,  -1,
            1,  0);

    M22T m3(
            4.683281e-01, 1.251189e-02,
            -8.749647e-01, 1.456563e-01);

    M22T m4(
            4.683281e-01, 1.251189e-02,
           -8.749647e-01, 1.456563e-01);

    TEST_MATRIX_INVERSE(m1, 0);
    TEST_MATRIX_INVERSE(m2, 0);
    TEST_MATRIX_INVERSE(m3, 20.0 * std::numeric_limits<TypeParam>::epsilon());
    TEST_MATRIX_INVERSE(m4, 20.0 * std::numeric_limits<TypeParam>::epsilon());
}

//------------------------------------------------------------------------------
// A macro to help with vector comparisons within floating point range.
#define EXPECT_VEC_EQ(VEC1, VEC2)                               \
do {                                                            \
    const decltype(VEC1) v1 = VEC1;                             \
    const decltype(VEC2) v2 = VEC2;                             \
    if (std::is_same<TypeParam,float>::value) {                 \
        for (size_t i = 0; i < v1.size(); ++i) {                \
            EXPECT_FLOAT_EQ(v1[i], v2[i]);                      \
        }                                                       \
    } else if (std::is_same<TypeParam,double>::value) {         \
        for (size_t i = 0; i < v1.size(); ++i) {                \
            EXPECT_DOUBLE_EQ(v1[i], v2[i]);                     \
        }                                                       \
    } else {                                                    \
        for (size_t i = 0; i < v1.size(); ++i) {                \
            EXPECT_EQ(v1[i], v2[i]);                            \
        }                                                       \
    }                                                           \
} while(0)

//------------------------------------------------------------------------------
// A macro to help with type comparisons within floating point range.
#define ASSERT_TYPE_EQ(T1, T2)                                  \
do {                                                            \
    const decltype(T1) t1 = T1;                                 \
    const decltype(T2) t2 = T2;                                 \
    if (std::is_same<TypeParam,float>::value) {                 \
        ASSERT_FLOAT_EQ(t1, t2);                                \
    } else if (std::is_same<TypeParam,double>::value) {         \
        ASSERT_DOUBLE_EQ(t1, t2);                               \
    } else {                                                    \
        ASSERT_EQ(t1, t2);                                      \
    }                                                           \
} while(0)

//------------------------------------------------------------------------------
// Test some translation stuff.
TYPED_TEST(MatTestT, Translation4) {
    typedef ::android::details::TMat44<TypeParam> M44T;
    typedef ::android::details::TVec4<TypeParam> V4T;

    V4T translateBy(-7.3, 1.1, 14.4, 0.0);
    V4T translation(translateBy[0], translateBy[1], translateBy[2], 1.0);
    M44T translation_matrix = M44T::translate(translation);

    V4T p1(9.9, 3.1, 41.1, 1.0);
    V4T p2(-18.0, 0.0, 1.77, 1.0);
    V4T p3(0, 0, 0, 1);
    V4T p4(-1000, -1000, 1000, 1.0);

    EXPECT_VEC_EQ(translation_matrix * p1, translateBy + p1);
    EXPECT_VEC_EQ(translation_matrix * p2, translateBy + p2);
    EXPECT_VEC_EQ(translation_matrix * p3, translateBy + p3);
    EXPECT_VEC_EQ(translation_matrix * p4, translateBy + p4);
}

//------------------------------------------------------------------------------
template <typename MATRIX>
static void verifyOrthonormal(const MATRIX& A) {
    typedef typename MATRIX::value_type T;

    static constexpr T value_eps = T(100) * std::numeric_limits<T>::epsilon();

    const MATRIX prod = A * transpose(A);
    for (size_t i = 0; i < MATRIX::NUM_COLS; ++i) {
        for (size_t j = 0; j < MATRIX::NUM_ROWS; ++j) {
            if (i == j) {
                ASSERT_NEAR(prod[i][j], T(1), value_eps);
            } else {
                ASSERT_NEAR(prod[i][j], T(0), value_eps);
            }
        }
    }
}

//------------------------------------------------------------------------------
// Test euler code.
TYPED_TEST(MatTestT, EulerZYX_44) {
    typedef ::android::details::TMat44<TypeParam> M44T;

    std::default_random_engine generator(82828);
    std::uniform_real_distribution<float> distribution(-6.0 * 2.0*M_PI, 6.0 * 2.0*M_PI);
    auto rand_gen = std::bind(distribution, generator);

    for (size_t i = 0; i < 100; ++i) {
        M44T m = M44T::eulerZYX(rand_gen(), rand_gen(), rand_gen());
        verifyOrthonormal(m);
    }

    M44T m = M44T::eulerZYX(1, 2, 3);
    verifyOrthonormal(m);
}

//------------------------------------------------------------------------------
// Test euler code.
TYPED_TEST(MatTestT, EulerZYX_33) {

    typedef ::android::details::TMat33<TypeParam> M33T;

    std::default_random_engine generator(112233);
    std::uniform_real_distribution<float> distribution(-6.0 * 2.0*M_PI, 6.0 * 2.0*M_PI);
    auto rand_gen = std::bind(distribution, generator);

    for (size_t i = 0; i < 100; ++i) {
        M33T m = M33T::eulerZYX(rand_gen(), rand_gen(), rand_gen());
        verifyOrthonormal(m);
    }

    M33T m = M33T::eulerZYX(1, 2, 3);
    verifyOrthonormal(m);
}

//------------------------------------------------------------------------------
// Test to quaternion with post translation.
TYPED_TEST(MatTestT, ToQuaternionPostTranslation) {

    typedef ::android::details::TMat44<TypeParam> M44T;
    typedef ::android::details::TVec4<TypeParam> V4T;
    typedef ::android::details::TQuaternion<TypeParam> QuatT;

    std::default_random_engine generator(112233);
    std::uniform_real_distribution<float> distribution(-6.0 * 2.0*M_PI, 6.0 * 2.0*M_PI);
    auto rand_gen = std::bind(distribution, generator);

    for (size_t i = 0; i < 100; ++i) {
        M44T r = M44T::eulerZYX(rand_gen(), rand_gen(), rand_gen());
        M44T t = M44T::translate(V4T(rand_gen(), rand_gen(), rand_gen(), 1));
        QuatT qr = r.toQuaternion();
        M44T tr = t * r;
        QuatT qtr = tr.toQuaternion();

        ASSERT_TYPE_EQ(qr.x, qtr.x);
        ASSERT_TYPE_EQ(qr.y, qtr.y);
        ASSERT_TYPE_EQ(qr.z, qtr.z);
        ASSERT_TYPE_EQ(qr.w, qtr.w);
    }

    M44T r = M44T::eulerZYX(1, 2, 3);
    M44T t = M44T::translate(V4T(20, -15, 2, 1));
    QuatT qr = r.toQuaternion();
    M44T tr = t * r;
    QuatT qtr = tr.toQuaternion();

    ASSERT_TYPE_EQ(qr.x, qtr.x);
    ASSERT_TYPE_EQ(qr.y, qtr.y);
    ASSERT_TYPE_EQ(qr.z, qtr.z);
    ASSERT_TYPE_EQ(qr.w, qtr.w);
}

//------------------------------------------------------------------------------
// Test to quaternion with post translation.
TYPED_TEST(MatTestT, ToQuaternionPointTransformation33) {
    static constexpr TypeParam value_eps =
            TypeParam(1000) * std::numeric_limits<TypeParam>::epsilon();

    typedef ::android::details::TMat33<TypeParam> M33T;
    typedef ::android::details::TVec3<TypeParam> V3T;
    typedef ::android::details::TQuaternion<TypeParam> QuatT;

    std::default_random_engine generator(112233);
    std::uniform_real_distribution<float> distribution(-100.0, 100.0);
    auto rand_gen = std::bind(distribution, generator);

    for (size_t i = 0; i < 100; ++i) {
        M33T r = M33T::eulerZYX(rand_gen(), rand_gen(), rand_gen());
        QuatT qr = r.toQuaternion();
        V3T p(rand_gen(), rand_gen(), rand_gen());

        V3T pr = r * p;
        V3T pq = qr * p;

        ASSERT_NEAR(pr.x, pq.x, value_eps);
        ASSERT_NEAR(pr.y, pq.y, value_eps);
        ASSERT_NEAR(pr.z, pq.z, value_eps);
    }
}

//------------------------------------------------------------------------------
// Test to quaternion with post translation.
TYPED_TEST(MatTestT, ToQuaternionPointTransformation44) {
    static constexpr TypeParam value_eps =
            TypeParam(1000) * std::numeric_limits<TypeParam>::epsilon();

    typedef ::android::details::TMat44<TypeParam> M44T;
    typedef ::android::details::TVec4<TypeParam> V4T;
    typedef ::android::details::TVec3<TypeParam> V3T;
    typedef ::android::details::TQuaternion<TypeParam> QuatT;

    std::default_random_engine generator(992626);
    std::uniform_real_distribution<float> distribution(-100.0, 100.0);
    auto rand_gen = std::bind(distribution, generator);

    for (size_t i = 0; i < 100; ++i) {
        M44T r = M44T::eulerZYX(rand_gen(), rand_gen(), rand_gen());
        QuatT qr = r.toQuaternion();
        V3T p(rand_gen(), rand_gen(), rand_gen());

        V4T pr = r * V4T(p.x, p.y, p.z, 1);
        pr.x /= pr.w;
        pr.y /= pr.w;
        pr.z /= pr.w;
        V3T pq = qr * p;

        ASSERT_NEAR(pr.x, pq.x, value_eps);
        ASSERT_NEAR(pr.y, pq.y, value_eps);
        ASSERT_NEAR(pr.z, pq.z, value_eps);
    }
}

#undef TEST_MATRIX_INVERSE

}; // namespace android
