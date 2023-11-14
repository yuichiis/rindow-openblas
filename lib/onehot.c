#include "matlib.h"
#include <math.h>

#define RINDOW_MATLIB_ONEHOT_INDEX_TYPE                         int32_t
#define RINDOW_MATLIB_ONEHOT_INDEX_DTYPE    rindow_matlib_dtype_int32
#define RINDOW_MATLIB_ONEHOT_INDEX_DTYPE_U  rindow_matlib_dtype_uint32

int32_t rindow_matlib_s_onehot(
    int32_t dtype, int32_t m, int32_t n, void *x, int32_t incX, float alpha, float *a, int32_t ldA)
{
    RINDOW_MATLIB_ONEHOT_INDEX_TYPE *indexes;
    int alloc_flag = 0;
    int errorCode = 0;

    if(rindow_matlib_common_dtype_to_valuesize(dtype)==0) {
        return -1;
    }
    if(dtype==RINDOW_MATLIB_ONEHOT_INDEX_DTYPE ||
        dtype==RINDOW_MATLIB_ONEHOT_INDEX_DTYPE_U) {
        indexes = x;
    } else {
        indexes = malloc(m*sizeof(RINDOW_MATLIB_ONEHOT_INDEX_TYPE));
        if(indexes==NULL) {
            return -1;
        }
        alloc_flag = 1;
        int32_t i;
        #pragma omp parallel for
        for(i=0;i<m;i++) {
            int64_t value;
            if(rindow_matlib_common_get_integer(dtype, x, incX, i, &value)) {
                errorCode = -1;
            }
            indexes[i] = (RINDOW_MATLIB_ONEHOT_INDEX_TYPE)value;
        }
        if(errorCode) {
            free(indexes);
            return errorCode;
        }
        incX = 1;
    }

    int32_t i;
    #pragma omp parallel for
    for(i=0;i<m;i++) {
        RINDOW_MATLIB_ONEHOT_INDEX_TYPE selector = indexes[i*incX];
        if(selector>=0 && selector<n) {
            a[i*ldA+selector] += alpha;
        } else {
            errorCode = -1;
        }
    }

    if(alloc_flag) {
        free(indexes);
    }
    return errorCode;
}

int32_t rindow_matlib_d_onehot(
    int32_t dtype, int32_t m, int32_t n, void *x, int32_t incX, double alpha, double *a, int32_t ldA)
{
    RINDOW_MATLIB_ONEHOT_INDEX_TYPE *indexes;
    int alloc_flag = 0;
    int errorCode = 0;

    if(rindow_matlib_common_dtype_to_valuesize(dtype)==0) {
        return -1;
    }
    if(dtype==RINDOW_MATLIB_ONEHOT_INDEX_DTYPE ||
        dtype==RINDOW_MATLIB_ONEHOT_INDEX_DTYPE_U) {
        indexes = x;
    } else {
        indexes = malloc(m*sizeof(RINDOW_MATLIB_ONEHOT_INDEX_TYPE));
        if(indexes==NULL) {
            return -1;
        }
        alloc_flag = 1;
        int32_t i;
        #pragma omp parallel for
        for(i=0;i<m;i++) {
            int64_t value;
            if(rindow_matlib_common_get_integer(dtype, x, incX, i, &value)) {
                errorCode = -1;
            }
            indexes[i] = (RINDOW_MATLIB_ONEHOT_INDEX_TYPE)value;
        }
        if(errorCode) {
            free(indexes);
            return errorCode;
        }
        incX = 1;
    }

    int32_t i;
    #pragma omp parallel for
    for(i=0;i<m;i++) {
        RINDOW_MATLIB_ONEHOT_INDEX_TYPE selector = indexes[i*incX];
        if(selector>=0 && selector<n) {
            a[i*ldA+selector] += alpha;
        } else {
            errorCode = -1;
        }
    }

    if(alloc_flag) {
        free(indexes);
    }
    return errorCode;
}

