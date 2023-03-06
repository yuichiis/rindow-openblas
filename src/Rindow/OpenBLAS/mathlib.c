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
    if(incX==1) {
        for(int32_t i=0; i<n; i++) {
            sum += x[i];
        }
    } else {
        int32_t i;
        #pragma omp parallel for reduction(+:sum)
        for(i=0; i<n; i++) {
            sum += x[i];
        }
    }
    return sum;
}

double rindow_math_mathlib_d_sum(int32_t n,double *x, int32_t incX, double sum)
{
    int32_t i;
    for(i=0; i<n; i++) {
        sum += x[i*incX];
    }
    return sum;
}

