#include "matlib.h"
#include "common.h"
#include <math.h>
#include <memory.h>

int32_t rindow_matlib_s_gather(
    int32_t reverse,
    int32_t addMode,
    int32_t n,
    int32_t k,
    int32_t numClass,
    int32_t dtype,
    void *x,
    float *a,
    float *b
)
{
    int32_t value_width = sizeof(float);

    int32_t errcode = 0;
    int32_t ldB = k;
    int32_t ldIndex = k;
    int64_t checktype;

    if(rindow_matlib_common_get_integer(dtype, x, 1, 0, &checktype)) {
        return RINDOW_MATLIB_E_UNSUPPORTED_DATA_TYPE;
    }

    int32_t i;
    #pragma omp parallel for
    for(i=0; i<n; i++) {
        int64_t selector = 0;
        rindow_matlib_common_get_integer(dtype, x, 1, i, &selector);
        if(selector<0||selector>=numClass) {
            errcode = RINDOW_MATLIB_E_PERM_OUT_OF_RANGE;
            continue;
        }
        float *from = &(a[selector*ldIndex]);
        float *to = &(b[i*ldB]);
        if(reverse) {
            float *tmp;
            tmp = from;
            from = to;
            to = tmp;
        }
        if(k==1) {
            if(addMode) {
                *to += *from;
            } else {
                *to = *from;
            }
        } else {
            if(addMode) {
                rindow_matlib_common_s_add(k, from, to);
            } else {
                memcpy(to, from,k*value_width);
            }
        }
    }
    return errcode;
}

int32_t rindow_matlib_d_gather(
    int32_t reverse,
    int32_t addMode,
    int32_t n,
    int32_t k,
    int32_t numClass,
    int32_t dtype,
    void *x,
    double *a,
    double *b
)
{
    int32_t value_width = sizeof(double);

    int32_t errcode = 0;
    int32_t ldB = k;
    int32_t ldIndex = k;
    int64_t checktype;

    if(rindow_matlib_common_get_integer(dtype, x, 1, 0, &checktype)) {
        return RINDOW_MATLIB_E_UNSUPPORTED_DATA_TYPE;
    }

    int32_t i;
    #pragma omp parallel for
    for(i=0; i<n; i++) {
        int64_t selector;
        rindow_matlib_common_get_integer(dtype, x, 1, i, &selector);
        if(selector<0||selector>=numClass) {
            errcode = RINDOW_MATLIB_E_PERM_OUT_OF_RANGE;
            continue;
        }
        double *from = &(a[selector*ldIndex]);
        double *to = &(b[i*ldB]);
        if(reverse) {
            double *tmp;
            tmp = from;
            from = to;
            to = tmp;
        }
        if(k==1) {
            if(addMode) {
                *to += *from;
            } else {
                *to = *from;
            }
        } else {
            if(addMode) {
                rindow_matlib_common_d_add(k, from, to);
            } else {
                memcpy(to, from,k*value_width);
            }
        }
    }
    return errcode;
}

int32_t rindow_matlib_i_gather(
    int32_t reverse,
    int32_t addMode,
    int32_t n,
    int32_t k,
    int32_t numClass,
    int32_t dtype,
    void *x,
    int32_t data_dtype,
    void *a,
    void *b
)
{
    int32_t errcode = 0;
    int32_t ldB = k;
    int32_t ldIndex = k;
    int64_t checktype;

    if(rindow_matlib_common_get_integer(dtype, x, 1, 0, &checktype)) {
        return RINDOW_MATLIB_E_UNSUPPORTED_DATA_TYPE;
    }
    if(!rindow_matlib_common_dtype_is_int(data_dtype) &&
        !rindow_matlib_common_dtype_is_bool(data_dtype)) {
        return RINDOW_MATLIB_E_UNSUPPORTED_DATA_TYPE;
    }
    int32_t value_width = rindow_matlib_common_dtype_to_valuesize(data_dtype);
    if(value_width==0) {
        return RINDOW_MATLIB_E_UNSUPPORTED_DATA_TYPE;
    }
    char *ax = a;
    char *bx = b;

    int32_t i;
    #pragma omp parallel for
    for(i=0; i<n; i++) {
        int64_t selector;
        rindow_matlib_common_get_integer(dtype, x, 1, i, &selector);
        if(selector<0||selector>=numClass) {
            errcode = RINDOW_MATLIB_E_PERM_OUT_OF_RANGE;
            continue;
        }
        char *from = &(ax[selector*ldIndex*value_width]);
        char *to = &(bx[i*ldB*value_width]);
        if(reverse) {
            char *tmp;
            tmp = from;
            from = to;
            to = tmp;
        }
        if(addMode) {
            rindow_matlib_common_i_add(k, data_dtype, from, to);
        } else {
            memcpy(to, from, k*value_width);
        }
    }

    return errcode;
}
