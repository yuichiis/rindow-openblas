#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "unitest.h"

#define RINDOW_MATLIB_INCLUDING_SOURCE 1
#include "../lib/matlib.c"
//#include "../lib/matlib.h"

//#define N 10000000
#define M 2
#define N 3
#define K 4


#define TEST_TRANSPOSE_FLOATFUNC(ftype) \
    rindow_matlib_##ftype##_transpose(\
        ndim,\
        shape,\
        perm,\
        a,\
        b\
    )

#define TEST_TRANSPOSE_INTFUNC(dtype) \
    rindow_matlib_i_transpose(\
        dtype,\
        ndim,\
        shape,\
        perm,\
        a,\
        b\
    )

#define TEST_TRANSPOSE_1D(type,ftype,atype,func) \
static char* test_##ftype##_transpose_1d()\
{\
    static type a[N];\
    static type b[N];\
    for(int i=0;i<N;i++) {\
        a[i] = (type)i;\
    }\
    for(int i=0;i<N;i++) {\
        b[i] = 0;\
    }\
    int32_t ndim = 1;\
    int32_t shape[1] = { N };\
    int32_t perm[1]  = { 0 };\
    int32_t rc;\
    rc = func;\
    ASSERT_EQUAL(d,0, rc)\
\
    for(int i=0;i<N;i++) {\
        ASSERT_EQUAL(atype,(type)i, b[i])\
    }\
    return NULL;\
}

#define TEST_TRANSPOSE_2D(type,ftype,atype,func) \
static char* test_##ftype##_transpose_2d()\
{\
    static type a[M*N];\
    static type b[M*N];\
    for(int i=0;i<M*N;i++) {\
        a[i] = (type)i;\
    }\
    for(int i=0;i<M*N;i++) {\
        b[i] = 0;\
    }\
    int32_t ndim = 2;\
    int32_t shape[2] = { M, N };\
    int32_t perm[2]  = { 1, 0 };\
    int32_t rc;\
    rc = func;\
    ASSERT_EQUAL(d,0, rc)\
\
    for(int i=0;i<N;i++) {\
        for(int j=0;j<M;j++) {\
            ASSERT_EQUAL(atype,(type)(j*N+i), b[i*M+j])\
        }\
    }\
    return NULL;\
}

#define TEST_TRANSPOSE_3D(type,ftype,atype,func) \
static char* test_##ftype##_transpose_3d()\
{\
    static type a[M*N*K];\
    static type b[M*N*K];\
    for(int i=0;i<M*N*K;i++) {\
        a[i] = (type)i;\
    }\
    for(int i=0;i<M*N*K;i++) {\
        b[i] = 0;\
    }\
    int32_t ndim = 3;\
    int32_t shape[3] = { M, N, K };\
    int32_t perm[3]  = { 2, 1, 0 };\
    int32_t rc;\
    rc = func;\
    ASSERT_EQUAL(d,0, rc)\
\
    for(int h=0;h<K;h++) {\
        for(int i=0;i<N;i++) {\
            for(int j=0;j<M;j++) {\
                ASSERT_EQUAL(atype,(type)(j*N*K+i*K+h), b[h*N*M+i*M+j])\
            }\
        }\
    }\
    return NULL;\
}

#define TEST_TRANSPOSE_3D2(type,ftype,atype,func) \
static char* test_##ftype##_transpose_3d2()\
{\
    static type a[M*N*K];\
    static type b[M*N*K];\
    for(int i=0;i<M*N*K;i++) {\
        a[i] = (type)i;\
    }\
    for(int i=0;i<M*N*K;i++) {\
        b[i] = 0;\
    }\
    int32_t ndim = 3;\
    int32_t shape[3] = { M, N, K };\
    int32_t perm[3]  = { 0, 2, 1 };\
    int32_t rc;\
    rc = func;\
    ASSERT_EQUAL(d,0, rc)\
\
    for(int h=0;h<M;h++) {\
        for(int i=0;i<K;i++) {\
            for(int j=0;j<N;j++) {\
                ASSERT_EQUAL(atype,(type)(h*K*N+j*K+i), b[h*K*N+i*N+j])\
            }\
        }\
    }\
    return NULL;\
}

TEST_TRANSPOSE_1D(float,s,f,TEST_TRANSPOSE_FLOATFUNC(s))
TEST_TRANSPOSE_2D(float,s,f,TEST_TRANSPOSE_FLOATFUNC(s))
TEST_TRANSPOSE_3D(float,s,f,TEST_TRANSPOSE_FLOATFUNC(s))
TEST_TRANSPOSE_3D2(float,s,f,TEST_TRANSPOSE_FLOATFUNC(s))
TEST_TRANSPOSE_1D(double,d,f,TEST_TRANSPOSE_FLOATFUNC(d))
TEST_TRANSPOSE_2D(double,d,f,TEST_TRANSPOSE_FLOATFUNC(d))
TEST_TRANSPOSE_3D(double,d,f,TEST_TRANSPOSE_FLOATFUNC(d))
TEST_TRANSPOSE_3D2(double,d,f,TEST_TRANSPOSE_FLOATFUNC(d))
TEST_TRANSPOSE_1D(int32_t,int,d,TEST_TRANSPOSE_INTFUNC(rindow_matlib_dtype_int32))
TEST_TRANSPOSE_2D(int32_t,int,d,TEST_TRANSPOSE_INTFUNC(rindow_matlib_dtype_int32))
TEST_TRANSPOSE_3D(int32_t,int,d,TEST_TRANSPOSE_INTFUNC(rindow_matlib_dtype_int32))
TEST_TRANSPOSE_3D2(int32_t,int,d,TEST_TRANSPOSE_INTFUNC(rindow_matlib_dtype_int32))


int main()
{
    TEST(test_s_transpose_1d)
    TEST(test_s_transpose_2d)
    TEST(test_s_transpose_3d)
    TEST(test_s_transpose_3d2)
    TEST(test_d_transpose_1d)
    TEST(test_d_transpose_2d)
    TEST(test_d_transpose_3d)
    TEST(test_d_transpose_3d2)
    TEST(test_i_transpose_1d)
    TEST(test_i_transpose_2d)
    TEST(test_i_transpose_3d)
    TEST(test_i_transpose_3d2)
}
