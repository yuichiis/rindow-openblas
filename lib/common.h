#ifndef RINDOW_MATLIB_COMMON_H_
#define RINDOW_MATLIB_COMMON_H_

#include <stdint.h>
#include <math.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t rindow_matlib_common_copy_ex(int32_t dtype,int32_t n,void* source,int32_t incSource,void* dest,int32_t incDest);
int32_t rindow_matlib_common_add_ex(int32_t dtype,int32_t n,void* source,int32_t incSource,void* dest,int32_t incDest);

int32_t rindow_matlib_common_get_integer(int32_t dtype, void *buffer, int32_t incWidth,int32_t index, int64_t *value);
int32_t rindow_matlib_common_set_integer(int32_t dtype, void *buffer, int32_t incWidth,int32_t index, int64_t value);

void rindow_matlib_common_s_add(int32_t n, float *x, float *y);
void rindow_matlib_common_d_add(int32_t n, double *x, double *y);
void rindow_matlib_common_i_add(int32_t n, int32_t dtype, void *x, void *y);
float rindow_matlib_common_s_sum_sb(int32_t n, float *x, int32_t incX);
double rindow_matlib_common_d_sum_sb(int32_t n, double *x, int32_t incX);
float rindow_matlib_common_s_max(int32_t n, float *x, int32_t incX);
double rindow_matlib_common_d_max(int32_t n, double *x, int32_t incX);
int32_t rindow_matlib_common_s_argmax(int32_t n, float *x, int32_t incX);
int32_t rindow_matlib_common_d_argmax(int32_t n, double *x, int32_t incX);
#if _MSC_VER
#define RINDOW_MATLIB_COMMON_RAND_MAX 0x7fffffff
#else
#define RINDOW_MATLIB_COMMON_RAND_MAX RAND_MAX
#endif
int32_t rindow_matlib_common_rand();
void rindow_matlib_common_srand(int32_t seed);

#ifdef __cplusplus
} // extern "C"
#endif

// RINDOW_MATLIB_COMMON_H_
#endif
