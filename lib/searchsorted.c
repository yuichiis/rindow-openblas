#include "matlib.h"
#include <math.h>

#define RINDOW_MATLIB_SEARCHSORTED_TEMPLATE(valuetype,a,x,y) \
    valuetype value = x[i*incX];      \
    int32_t j;                        \
    if(right) {                       \
        for(j=0;j<m;j++) {            \
            if(!(value>=a[j*incA])) { \
                break;                \
            }                         \
        }                             \
    } else {                          \
        for(j=0;j<m;j++) {            \
            if(!(value>a[j*incA])) {  \
                break;                \
            }                         \
        }                             \
    }                                 \
    rindow_matlib_common_set_integer(dtype, y, incY, i, j); \


void rindow_matlib_s_searchsorted(
    int32_t m,
    float *a, int32_t incA,
    int32_t n,
    float *x, int32_t incX,
    int32_t right,
    int32_t dtype, void *y, int32_t incY)
{
    int32_t i;
    #pragma omp parallel for
    for(i=0;i<n;i++) {
        RINDOW_MATLIB_SEARCHSORTED_TEMPLATE(float,a,x,y)
    }
}

void rindow_matlib_d_searchsorted(
    int32_t m,
    double *a, int32_t incA,
    int32_t n,
    double *x, int32_t incX,
    int32_t right,
    int32_t dtype, void *y, int32_t incY)
{
    int32_t i;
    #pragma omp parallel for
    for(i=0;i<n;i++) {
        RINDOW_MATLIB_SEARCHSORTED_TEMPLATE(double,a,x,y)
    }
}
