#include "mathlib.h"
#include <math.h>
#ifndef _OPENMP
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <stdio.h>
typedef struct _arg_s_sum_kernel {
    pthread_t tid;
    float sum;
    int32_t n;
    float *x;
    int32_t incX;
} arg_s_sum_kernel_t;
typedef struct _arg_d_sum_kernel {
    pthread_t tid;
    double sum;
    int32_t n;
    double *x;
    int32_t incX;
} arg_d_sum_kernel_t;
#endif

static void *s_sum_kernel(void *varg)
{
    arg_s_sum_kernel_t *arg=varg;
    int32_t i;
    float sum=0;
    int32_t n = arg->n;
    float* x = arg->x;
    int32_t incX = arg->incX;
    for(i=0; i<arg->n; i++) {
        sum += x[i*incX];
    }
    arg->sum = sum;

    return NULL;
}
static void *d_sum_kernel(void *varg)
{
    arg_d_sum_kernel_t *arg=varg;
    int32_t i;
    double sum=0;
    int32_t n = arg->n;
    double* x = arg->x;
    int32_t incX = arg->incX;
    for(i=0; i<arg->n; i++) {
        sum += x[i*incX];
    }
    arg->sum = sum;

    return NULL;
}

float rindow_math_mathlib_s_sum(int32_t n,float *x, int32_t incX, float sum)
{
#ifdef _OPENMP
    int32_t i;
    #pragma omp parallel for reduction(+:sum)
    for(i=0; i<n; i++) {
        sum += x[i*incX];
    }
    return sum;
#else
    int32_t num_thread = get_nprocs();
    int32_t cell_size = n/num_thread;
    int32_t remainder = n-cell_size*num_thread;
    //printf("#num_thread=%d\n",num_thread);
    //printf("#cell_size=%d\n",cell_size);
    //printf("#remainder=%d\n",remainder);
    arg_s_sum_kernel_t *th_arg=calloc(num_thread,sizeof(arg_s_sum_kernel_t));
    int32_t i;
    for(i=0;i<num_thread;i++) {
        if(i==num_thread-1) {
            th_arg[i].n = cell_size+remainder;
        } else {
            th_arg[i].n = cell_size;
        }
        th_arg[i].x = &x[i*cell_size*incX];
        th_arg[i].incX = incX;
        th_arg[i].sum = 0.0;
        pthread_create( &(th_arg[i].tid), NULL, &s_sum_kernel, &th_arg[i]);
    }
    for(i=0;i<num_thread;i++) {
        pthread_join(th_arg[i].tid,NULL);
        sum += th_arg[i].sum;
    }
    free(th_arg);
    return sum;
#endif
}

double rindow_math_mathlib_d_sum(int32_t n,double *x, int32_t incX, double sum)
{
#ifdef _OPENMP
    int32_t i;
    #pragma omp parallel for reduction(+:sum)
    for(i=0; i<n; i++) {
        sum += x[i*incX];
    }
    return sum;
#else
    int32_t num_thread = get_nprocs();
    int32_t cell_size = n/num_thread;
    int32_t remainder = n-cell_size*num_thread;
    //printf("#num_thread=%d\n",num_thread);
    //printf("#cell_size=%d\n",cell_size);
    //printf("#remainder=%d\n",remainder);
    arg_d_sum_kernel_t *th_arg=calloc(num_thread,sizeof(arg_d_sum_kernel_t));
    int32_t i;
    for(i=0;i<num_thread;i++) {
        if(i==num_thread-1) {
            th_arg[i].n = cell_size+remainder;
        } else {
            th_arg[i].n = cell_size;
        }
        th_arg[i].x = &x[i*cell_size*incX];
        th_arg[i].incX = incX;
        th_arg[i].sum = 0.0;
        pthread_create( &(th_arg[i].tid), NULL, &d_sum_kernel, &th_arg[i]);
    }
    for(i=0;i<num_thread;i++) {
        pthread_join(th_arg[i].tid,NULL);
        sum += th_arg[i].sum;
    }
    free(th_arg);
    return sum;
#endif
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

