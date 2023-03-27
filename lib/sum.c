#include "mathlib.h"
#include <math.h>

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



#define PHP_RINDOW_OPENBLAS_MATH_SUM_TEMPLATE(data_type) { \
    data_type  *pDataX=x; \
    for(int i=0; i<n; i++,pDataX+=incX) { \
        sum += *pDataX; \
    } \
}

int64_t rindow_math_mathlib_int_sum(int32_t dtype, int32_t n,void *x, int32_t incX, int64_t sum)
{
    switch(dtype) {
        case rindow_math_mathlib_dtype_int8: {
            PHP_RINDOW_OPENBLAS_MATH_SUM_TEMPLATE(int8_t)
            break;
        }
        case rindow_math_mathlib_dtype_uint8: {
            PHP_RINDOW_OPENBLAS_MATH_SUM_TEMPLATE(uint8_t)
            break;
        }
        case rindow_math_mathlib_dtype_int16: {
            PHP_RINDOW_OPENBLAS_MATH_SUM_TEMPLATE(int16_t)
            break;
        }
        case rindow_math_mathlib_dtype_uint16: {
            PHP_RINDOW_OPENBLAS_MATH_SUM_TEMPLATE(uint16_t)
            break;
        }
        case rindow_math_mathlib_dtype_int32: {
            PHP_RINDOW_OPENBLAS_MATH_SUM_TEMPLATE(int32_t)
            break;
        }
        case rindow_math_mathlib_dtype_uint32: {
            PHP_RINDOW_OPENBLAS_MATH_SUM_TEMPLATE(uint32_t)
            break;
        }
        case rindow_math_mathlib_dtype_int64: {
            PHP_RINDOW_OPENBLAS_MATH_SUM_TEMPLATE(int64_t)
            break;
        }
        case rindow_math_mathlib_dtype_uint64: {
            PHP_RINDOW_OPENBLAS_MATH_SUM_TEMPLATE(uint64_t)
            break;
        }
        case rindow_math_mathlib_dtype_bool: {
                uint8_t *pBoolX = x;
                for (int i=0; i<n; i++,pBoolX+=incX) {
                    if(*pBoolX!=0) {
                        sum += 1;
                    }
                }
            break;
        }
    }
    return sum;
}

