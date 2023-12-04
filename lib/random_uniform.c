#include "matlib.h"
#include <math.h>
#include <stdlib.h>
#include "common.h"

static inline float rindow_matlib_s_random_range_sub(
    float low,float high)
{
    return low+(float)rindow_matlib_common_rand()/(float)RINDOW_MATLIB_COMMON_RAND_MAX/(float)2.0*(high-low);
}

static inline double rindow_matlib_d_random_range_sub(
    double low,double high)
{
    return low+(double)rindow_matlib_common_rand()/(double)RINDOW_MATLIB_COMMON_RAND_MAX/2.0*(high-low);
}

static inline int32_t rindow_matlib_i_random_range_sub(
    int32_t low,int32_t high)
{
    if(high-low==RINDOW_MATLIB_COMMON_RAND_MAX) {
        return rindow_matlib_common_rand();
    }
    return (rindow_matlib_common_rand()%(high-low+1))+low;
}

void rindow_matlib_s_randomuniform(
    int32_t n,
    float *x, int32_t incX,
    float low,
    float high,
    int32_t seed
)
{
    if(seed!=0) {
        rindow_matlib_common_srand(seed);
    }
    for(int32_t i=0; i<n; i++) {
        x[i*incX] = rindow_matlib_s_random_range_sub(low,high);
    }
}

void rindow_matlib_d_randomuniform(
    int32_t n,
    double *x, int32_t incX,
    double low,
    double high,
    int32_t seed
)
{
    if(seed!=0) {
        rindow_matlib_common_srand(seed);
    }
    for(int32_t i=0; i<n; i++) {
        x[i*incX] = rindow_matlib_d_random_range_sub(low,high);
    }
}

void rindow_matlib_i_randomuniform(
    int32_t n,
    int32_t dtype,
    double *x, int32_t incX,
    int32_t low,
    int32_t high,
    int32_t seed
)
{
    if(seed!=0) {
        rindow_matlib_common_srand(seed);
    }
    for(int32_t i=0; i<n; i++) {
        int64_t value = rindow_matlib_i_random_range_sub(low,high);
        rindow_matlib_common_set_integer(dtype, x, incX, i, value);
    }
}
