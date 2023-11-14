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
#include "greater.c"
#include "greater_eq.c"
#include "less.c"
#include "less_eq.c"
#include "multiply.c"
#include "add.c"
#include "duplicate.c"
#include "square.c"
#include "sqrt.c"
#include "rsqrt.c"
#include "pow.c"
#include "exp.c"
#include "log.c"
#include "tanh.c"
#include "sin.c"
#include "cos.c"
#include "tan.c"
#include "zeros.c"
#include "onehot.c"
#include "softmax.c"
#include "equal.c"
#include "not_equal.c"
#include "not.c"
#include "astype.c"
#include "matrixcopy.c"
#include "imagecopy.c"
#include "fill.c"
#include "nan2num.c"
#include "isnan.c"
#include "searchsorted.c"
#include "cumsum.c"
#include "gather.c"
#include "reduce_gather.c"

#include "transpose.c"
#include "bandpart.c"
