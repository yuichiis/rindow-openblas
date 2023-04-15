#include "matlib.h"
#include <math.h>

void rindow_matlib_s_minimum(
    int32_t m,
    int32_t n,
    float *a, int32_t ldA,
    float *x, int32_t incX
    )
{
    if(m>n) {
        int32_t i;
        #pragma omp parallel for
        for(i=0;i<m;i++) {
            int32_t j;
            for(j=0;j<n;j++) {
                float value = x[j*incX];
                if(isnan(value)) {
                    a[i*ldA+j] = value;
                } else {
                    // *** CAUTION ***
                    // if NaN then don't set alpha
                    if(a[i*ldA+j] > value) {
                        a[i*ldA+j] = value;
                    }
                }
            }
        }
    } else {
        int32_t j;
        #pragma omp parallel for
        for(j=0;j<n;j++) {
            float value = x[j*incX];
            int32_t i;
            for(i=0;i<m;i++) {
                if(isnan(value)) {
                    a[i*ldA+j] = value;
                } else {
                    // *** CAUTION ***
                    // if NaN then don't set alpha
                    if(a[i*ldA+j] > value) {
                        a[i*ldA+j] = value;
                    }
                }
            }
        }
    }
}

void rindow_matlib_d_minimum(
    int32_t m,
    int32_t n,
    double *a, int32_t ldA,
    double *x, int32_t incX
    )
{
    if(m>n) {
        int32_t i;
        #pragma omp parallel for
        for(i=0;i<m;i++) {
            int32_t j;
            for(j=0;j<n;j++) {
                double value = x[j*incX];
                if(isnan(value)) {
                    a[i*ldA+j] = value;
                } else {
                    // *** CAUTION ***
                    // if NaN then don't set alpha
                    if(a[i*ldA+j] > value) {
                        a[i*ldA+j] = value;
                    }
                }
            }
        }
    } else {
        int32_t j;
        #pragma omp parallel for
        for(j=0;j<n;j++) {
            double value = x[j*incX];
            int32_t i;
            for(i=0;i<m;i++) {
                if(isnan(value)) {
                    a[i*ldA+j] = value;
                } else {
                    // *** CAUTION ***
                    // if NaN then don't set alpha
                    if(a[i*ldA+j] > value) {
                        a[i*ldA+j] = value;
                    }
                }
            }
        }
    }
}
