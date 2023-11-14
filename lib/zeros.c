#include "matlib.h"
#include <math.h>

#define RINDOW_MATLIB_ZEROS_TEMPLATE(x,i,incX) \
    for(i=0;i<n;i++) { \
        x[i*incX] = 0.0; \
    }


void rindow_matlib_s_zeros(int32_t n, float *x, int32_t incX)
{
    if(incX==1) {
        memset(x,0,sizeof(float)*n);
    } else {
        int32_t i;
        #pragma omp parallel for
        RINDOW_MATLIB_ZEROS_TEMPLATE(x,i,incX)
    }
}

void rindow_matlib_d_zeros(int32_t n, double *x, int32_t incX)
{
    if(incX==1) {
        memset(x,0,sizeof(double)*n);
    } else {
        int32_t i;
        #pragma omp parallel for
        RINDOW_MATLIB_ZEROS_TEMPLATE(x,i,incX)
    }
}

void rindow_matlib_i_zeros(int32_t dtype, int32_t n,void *x, int32_t incX)
{
    size_t valueSize = rindow_matlib_common_dtype_to_valuesize(dtype);
    if(valueSize==0) {
        return;
    }
    if(incX==1) {
        memset(x,0,valueSize*n);
    } else {
        int32_t i;
        #pragma omp parallel for
        for(i=0;i<n;i++) {
            memset(&((char *)x)[i*incX*valueSize],0,valueSize);
        }
    }
}
