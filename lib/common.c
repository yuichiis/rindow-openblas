#include "matlib.h"
#include "common.h"
#include <math.h>

#define RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(data_type) { \
    data_type  *pDataX; \
    data_type  *pDataY; \
    pDataX = (data_type *)source; \
    pDataY = (data_type *)dest; \
    for (i=0; i<n; i++) { \
        *pDataY = *pDataX; \
        pDataX+=incSource; \
        pDataY+=incDest; \
    } \
}

int32_t rindow_matlib_common_copy_ex(
    int32_t dtype,
    int32_t n,
    void* source,
    int32_t incSource,
    void* dest,
    int32_t incDest
    )
{
    switch (dtype) {
        int32_t i;
        case rindow_matlib_dtype_float32:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(float)
            break;
        case rindow_matlib_dtype_float64:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(double)
            break;
        case rindow_matlib_dtype_bool:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(int8_t)
            break;
        case rindow_matlib_dtype_int8:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(int8_t)
            break;
        case rindow_matlib_dtype_uint8:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(uint8_t)
            break;
        case rindow_matlib_dtype_int16:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(int16_t)
            break;
        case rindow_matlib_dtype_uint16:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(uint16_t)
            break;
        case rindow_matlib_dtype_int32:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(int32_t)
            break;
        case rindow_matlib_dtype_uint32:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(uint32_t)
            break;
        case rindow_matlib_dtype_int64:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(int64_t)
            break;
        case rindow_matlib_dtype_uint64:
            RINDOW_MATLIB_COMMON_COPY_EX_TEMPLATE(uint64_t)
            break;
        default:
            return -1;
    }
    return 0;
}

#define RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(data_type) { \
    data_type  *pDataX; \
    data_type  *pDataY; \
    pDataX = (data_type *)source; \
    pDataY = (data_type *)dest; \
    for (i=0; i<n; i++) { \
        *pDataY += *pDataX; \
        pDataX+=incSource; \
        pDataY+=incDest; \
    } \
}

int32_t rindow_matlib_common_add_ex(
    int32_t dtype,
    int32_t n,
    void* source,
    int32_t incSource,
    void* dest,
    int32_t incDest
    )
{
    switch (dtype) {
        int32_t i;
        case rindow_matlib_dtype_float32:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(float)
            break;
        case rindow_matlib_dtype_float64:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(double)
            break;
        case rindow_matlib_dtype_bool:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(int8_t)
            break;
        case rindow_matlib_dtype_int8:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(int8_t)
            break;
        case rindow_matlib_dtype_uint8:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(uint8_t)
            break;
        case rindow_matlib_dtype_int16:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(int16_t)
            break;
        case rindow_matlib_dtype_uint16:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(uint16_t)
            break;
        case rindow_matlib_dtype_int32:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(int32_t)
            break;
        case rindow_matlib_dtype_uint32:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(uint32_t)
            break;
        case rindow_matlib_dtype_int64:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(int64_t)
            break;
        case rindow_matlib_dtype_uint64:
            RINDOW_MATLIB_COMMON_ADD_EX_TEMPLATE(uint64_t)
            break;
        default:
            return -1;
    }
    return 0;
}


void* rindow_matlib_common_get_address(
    int32_t dtype, void *buffer, int32_t offset)
{
    size_t valueSize = rindow_matlib_common_dtype_to_valuesize(dtype);
    if(valueSize==0) {
        return NULL;
    }
    return ((char *)buffer)+(valueSize*offset);
}

#define RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(data_type,value_type) { \
    data_type *x = (data_type *)buffer; \
    *value = (value_type)(x[index*incWidth]);  \
    return 0; \
}

#define RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(data_type) { \
    data_type *x = (data_type *)buffer; \
    x[index*incWidth] = (data_type)value;  \
    return 0; \
}

int32_t rindow_matlib_common_get_integer(
    int32_t dtype, void *buffer, int32_t incWidth,
    int32_t index, int64_t *value)
{
    switch (dtype) {
        case rindow_matlib_dtype_bool: {
            uint8_t *x = (uint8_t *)buffer;
            if(x[index*incWidth]==0) { *value = 0; }
            else                     { *value = 1; }
            return 0;
        }
        case rindow_matlib_dtype_int8:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(int8_t,   int64_t);
        case rindow_matlib_dtype_uint8:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(uint8_t,  int64_t);
        case rindow_matlib_dtype_int16:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(int16_t,  int64_t);
        case rindow_matlib_dtype_uint16:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(uint16_t, int64_t);
        case rindow_matlib_dtype_int32:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(int32_t,  int64_t);
        case rindow_matlib_dtype_uint32:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(uint32_t, int64_t);
        case rindow_matlib_dtype_int64:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(int64_t,  int64_t);
        case rindow_matlib_dtype_uint64:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(uint64_t, int64_t);
        case rindow_matlib_dtype_float32:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(float,    int64_t);
        case rindow_matlib_dtype_float64:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(double,   int64_t);
        default:
            return -1;
    }
}

int32_t rindow_matlib_common_set_integer(
    int32_t dtype, void *buffer, int32_t incWidth,
    int32_t index, int64_t value)
{
    switch (dtype) {
        case rindow_matlib_dtype_bool:
        {
            uint8_t *x = (uint8_t *)buffer;
            if(value==0) { x[index*incWidth]=0; }
            else         { x[index*incWidth]=1; }
            return 0;
        }
        case rindow_matlib_dtype_int8:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(int8_t);
        case rindow_matlib_dtype_uint8:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(uint8_t);
        case rindow_matlib_dtype_int16:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(int16_t);
        case rindow_matlib_dtype_uint16:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(uint16_t);
        case rindow_matlib_dtype_int32:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(int32_t);
        case rindow_matlib_dtype_uint32:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(uint32_t);
        case rindow_matlib_dtype_int64:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(int64_t);
        case rindow_matlib_dtype_uint64:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(uint64_t);
        case rindow_matlib_dtype_float32:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(float);
        case rindow_matlib_dtype_float64:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(double);
        default:
            return -1;
    }
}

int32_t rindow_matlib_common_get_float(
    int32_t dtype, void *buffer, int32_t incWidth,
    int32_t index, double *value)
{
    switch (dtype) {
        case rindow_matlib_dtype_bool: {
            uint8_t *x = (uint8_t *)buffer;
            if(x[index*incWidth]==0) { *value = 0; }
            else                     { *value = 1; }
            return 0;
        }
        case rindow_matlib_dtype_int8:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(int8_t,   double);
        case rindow_matlib_dtype_uint8:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(uint8_t,  double);
        case rindow_matlib_dtype_int16:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(int16_t,  double);
        case rindow_matlib_dtype_uint16:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(uint16_t, double);
        case rindow_matlib_dtype_int32:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(int32_t,  double);
        case rindow_matlib_dtype_uint32:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(uint32_t, double);
        case rindow_matlib_dtype_int64:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(int64_t,  double);
        case rindow_matlib_dtype_uint64:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(uint64_t, double);
        case rindow_matlib_dtype_float32:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(float,    double);
        case rindow_matlib_dtype_float64:
            RINDOW_MATLIB_COMMON_GET_CAST_TEMPLATE(double,   double);
        default:
            return -1;
    }
}

int32_t rindow_matlib_common_set_float(
    int32_t dtype, void *buffer, int32_t incWidth,
    int32_t index, double value)
{
    switch (dtype) {
        case rindow_matlib_dtype_bool:
        {
            uint8_t *x = (uint8_t *)buffer;
            if(value==0) { x[index*incWidth]=0; }
            else         { x[index*incWidth]=1; }
            return 0;
        }
        case rindow_matlib_dtype_int8:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(int8_t);
        case rindow_matlib_dtype_uint8:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(uint8_t);
        case rindow_matlib_dtype_int16:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(int16_t);
        case rindow_matlib_dtype_uint16:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(uint16_t);
        case rindow_matlib_dtype_int32:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(int32_t);
        case rindow_matlib_dtype_uint32:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(uint32_t);
        case rindow_matlib_dtype_int64:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(int64_t);
        case rindow_matlib_dtype_uint64:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(uint64_t);
        case rindow_matlib_dtype_float32:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(float);
        case rindow_matlib_dtype_float64:
            RINDOW_MATLIB_COMMON_SET_CAST_TEMPLATE(double);
        default:
            return -1;
    }
}

void rindow_matlib_common_s_add(int32_t n, float *x, float *y)
{
    int32_t i;
    #pragma omp simd
    for(i=0; i<n; i++) {
        y[i] += x[i];
    }
}

void rindow_matlib_common_d_add(int32_t n, double *x, double *y)
{
    int32_t i;
    #pragma omp simd
    for(i=0; i<n; i++) {
        y[i] += x[i];
    }
}

#define RINDOW_MATLIB_COMMON_I_ADD_TEMPLATE(n,i,x,y) \
    for(i=0; i<n; i++) { \
        y[i] += x[i];    \
    }

void rindow_matlib_common_i_add(int32_t n, int32_t dtype, void *x, void *y)
{
    switch (dtype)
    {
        case rindow_matlib_dtype_bool: {
            int8_t *typed_x=x;
            int8_t *typed_y=y;
            int32_t i;
            #pragma omp simd
            for(i=0;i<n;i++) {
                typed_y[i] |= typed_x[i];
            }
            break;
        }
        case rindow_matlib_dtype_int8: {
            int8_t *typed_x=x;
            int8_t *typed_y=y;
            int32_t i;
            #pragma omp simd
            RINDOW_MATLIB_COMMON_I_ADD_TEMPLATE(n,i,typed_x,typed_y)
            break;
        }
        case rindow_matlib_dtype_uint8: {
            uint8_t *typed_x=x;
            uint8_t *typed_y=y;
            int32_t i;
            #pragma omp simd
            RINDOW_MATLIB_COMMON_I_ADD_TEMPLATE(n,i,typed_x,typed_y)
            break;
        }
        case rindow_matlib_dtype_int16: {
            int16_t *typed_x=x;
            int16_t *typed_y=y;
            int32_t i;
            #pragma omp simd
            RINDOW_MATLIB_COMMON_I_ADD_TEMPLATE(n,i,typed_x,typed_y)
            break;
        }
        case rindow_matlib_dtype_uint16: {
            uint16_t *typed_x=x;
            uint16_t *typed_y=y;
            int32_t i;
            #pragma omp simd
            RINDOW_MATLIB_COMMON_I_ADD_TEMPLATE(n,i,typed_x,typed_y)
            break;
        }
        case rindow_matlib_dtype_int32: {
            int32_t *typed_x=x;
            int32_t *typed_y=y;
            int32_t i;
            #pragma omp simd
            RINDOW_MATLIB_COMMON_I_ADD_TEMPLATE(n,i,typed_x,typed_y)
            break;
        }
        case rindow_matlib_dtype_uint32: {
            uint32_t *typed_x=x;
            uint32_t *typed_y=y;
            int32_t i;
            #pragma omp simd
            RINDOW_MATLIB_COMMON_I_ADD_TEMPLATE(n,i,typed_x,typed_y)
            break;
        }
        case rindow_matlib_dtype_int64: {
            int64_t *typed_x=x;
            int64_t *typed_y=y;
            int32_t i;
            #pragma omp simd
            RINDOW_MATLIB_COMMON_I_ADD_TEMPLATE(n,i,typed_x,typed_y)
            break;
        }
        case rindow_matlib_dtype_uint64: {
            uint64_t *typed_x=x;
            uint64_t *typed_y=y;
            int32_t i;
            #pragma omp simd
            RINDOW_MATLIB_COMMON_I_ADD_TEMPLATE(n,i,typed_x,typed_y)
            break;
        }
        default: {
            break;
        }
    }
}

float rindow_matlib_common_s_sum_sb(int32_t n, float *x, int32_t incX)
{
    float a=0;
    for(int32_t i=0; i<n; i++) {
        a += x[i*incX];
    }
    return a;
}

double rindow_matlib_common_d_sum_sb(int32_t n, double *x, int32_t incX)
{
    double a=0;
    for(int32_t i=0; i<n; i++) {
        a += x[i*incX];
    }
    return a;
}

float rindow_matlib_common_s_max(int32_t n, float *x, int32_t incX)
{
    float a;
    a = x[0];
    for(int32_t i=1;i<n;i++) {
        // if NaN set NaN
        // Compatible with reduce_max of tensorflow 2.6
        if(!(a>=x[i*incX])) {
            a = x[i*incX];
        }
    }
    return a;
}

double rindow_matlib_common_d_max(int32_t n, double *x, int32_t incX)
{
    double a;
    a = x[0];
    for(int32_t i=1;i<n;i++) {
        // if NaN set NaN
        // Compatible with reduce_max of tensorflow 2.6
        if(!(a>=x[i*incX])) {
            a = x[i*incX];
        }
    }
    return a;
}

int32_t rindow_matlib_common_s_argmax(int32_t n, float *x, int32_t incX)
{
    int32_t i;
    int32_t idx;
    float a;
    idx = 0;
    a = x[0];
    for(i=1;i<n;i++) {
        if(a<x[i*incX]) {
            idx = i;
            a = x[i*incX];
        }
    }
    return idx;
}

int32_t rindow_matlib_common_d_argmax(int32_t n, double *x, int32_t incX)
{
    int32_t i;
    int32_t idx;
    double a;
    idx = 0;
    a = x[0];
    for(i=1;i<n;i++) {
        if(a<x[i*incX]) {
            idx = i;
            a = x[i*incX];
        }
    }
    return idx;
}


int32_t rindow_matlib_common_rand()
{
#if _MSC_VER
    unsigned int number;
    if(rand_s( &number )) {
        return 0;
    }
    return (int32_t)number & 0x7fffffff;
#else
    return random();
#endif
}
void rindow_matlib_common_srand(int32_t seed)
{
#if _MSC_VER
#else
    srandom(seed);
#endif
}