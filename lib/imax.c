#include "mathlib.h"
#include <math.h>

int32_t rindow_math_mathlib_s_imax(int32_t n,float *x, int32_t incX, float floatMax)
{
    int32_t resultIdx = -1;
    #pragma omp parallel
    {
        int32_t i;
        float maxVal=floatMax;
        int32_t maxIdx=-1;
        #pragma omp for
        for(i=0; i<n; i++) {
            if(maxVal<x[i*incX] || isnan(maxVal)) {
                maxVal = x[i*incX];
                maxIdx = i;
            }
        }
        #pragma omp critical
        {
            if(floatMax<maxVal || isnan(floatMax)) {
                floatMax = maxVal;
                resultIdx = maxIdx;
            }
        }
    }
    return resultIdx;
}

int32_t rindow_math_mathlib_d_imax(int32_t n,double *x, int32_t incX, double floatMax)
{
    int32_t resultIdx = -1;
    #pragma omp parallel
    {
        int32_t i;
        double maxVal=floatMax;
        int32_t maxIdx=-1;
        #pragma omp for
        for(i=0; i<n; i++) {
            if(maxVal<x[i*incX] || isnan(maxVal)) {
                maxVal = x[i*incX];
                maxIdx = i;
            }
        }
        #pragma omp critical
        {
            if(floatMax<maxVal || isnan(floatMax)) {
                floatMax = maxVal;
                resultIdx = maxIdx;
            }
        }
    }
    return resultIdx;
}

