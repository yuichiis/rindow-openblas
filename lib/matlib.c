#include "matlib.h"

#ifndef _OPENMP

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

#endif // ifndef _OPENMP

#include "common.c"
#include "sum.c"
#include "imax.c"
#include "imin.c"
#include "increment.c"
#include "reciprocal.c"
#include "maximum.c"
#include "minimum.c"

#include "transpose.c"
#include "bandpart.c"
