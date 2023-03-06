#include "mathlib.h"

void rindow_math_mathlib_s_increment(int32_t n, float *x, int32_t incX, float alpha, float beta)
{
    if(incX==1) {
        long i;
        #pragma omp simd
        for(i=0;i<n;i++) {
            x[i] = alpha * x[i] + beta;
        }
    } else {
        long i;
        #pragma omp parallel for
        for(i=0;i<n;i++) {
            x[i*incX] = alpha * x[i*incX] + beta;
        }
    }
}

void rindow_math_mathlib_d_increment(int32_t n, double *x, int32_t incX, double alpha, double beta)
{
    if(incX==1) {
        long i;
        #pragma omp simd
        for(i=0;i<n;i++) {
            x[i] = alpha * x[i] + beta;
        }
    } else {
        long i;
        #pragma omp parallel for
        for(i=0;i<n;i++) {
            x[i*incX] = alpha * x[i*incX] + beta;
        }
    }
}

float rindow_math_mathlib_s_sum(int32_t n,float *x, int32_t incX, float sum)
{
    int32_t i;
    #pragma omp parallel for reduction(+:sum)
    for(i=0; i<n; i++) {
        sum += x[i];
    }
    return sum;
}

double rindow_math_mathlib_d_sum(int32_t n,double *x, int32_t incX, double sum)
{
    int32_t i;
    #pragma omp parallel for reduction(+:sum)
    for(i=0; i<n; i++) {
        sum += x[i*incX];
    }
    return sum;
}

int32_t rindow_math_mathlib_s_imax(int32_t n,float *x, int32_t incX, float floatMax)
{
    int32_t resultIdx = -1;
    #pragma omp parallel
    {
        int32_t i;
        float maxVal=floatMax;
        float maxIdx=-1;
        #pragma omp for
        for(i=0; i<n; i++) {
            if(maxVal<x[i] || isnan(maxVal)) {
                maxVal = x[i];
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
        double maxIdx=-1;
        #pragma omp for
        for(i=0; i<n; i++) {
            if(maxVal<x[i] || isnan(maxVal)) {
                maxVal = x[i];
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

int32_t rindow_math_mathlib_s_imin(int32_t n,float *x, int32_t incX, float floatMin)
{
    int32_t resultIdx = -1;
    #pragma omp parallel
    {
        int32_t i;
        float minVal=floatMin;
        float minIdx=-1;
        #pragma omp for
        for(i=0; i<n; i++) {
            if(minVal>x[i]) {
                minVal = x[i];
                minIdx = i;
            }
        }
        #pragma omp critical
        {
            if(floatMin>minVal) {
                floatMin = minVal;
                resultIdx = minIdx;
            }
        }
    }
    return resultIdx;
}

int32_t rindow_math_mathlib_d_imin(int32_t n,double *x, int32_t incX, double floatMin)
{
    int32_t resultIdx = -1;
    #pragma omp parallel
    {
        int32_t i;
        double minVal=floatMin;
        double minIdx=-1;
        #pragma omp for
        for(i=0; i<n; i++) {
            if(minVal>x[i]) {
                minVal = x[i];
                minIdx = i;
            }
        }
        #pragma omp critical
        {
            if(floatMin>minVal) {
                floatMin = minVal;
                resultIdx = minIdx;
            }
        }
    }
    return resultIdx;
}

