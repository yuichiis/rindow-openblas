#ifndef RINDOW_MATLIB_COMMON_H_
#define RINDOW_MATLIB_COMMON_H_

#include <stdint.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif
void rindow_matlib_common_s_add(int32_t n, float *x, float *y);
void rindow_matlib_common_d_add(int32_t n, double *x, double *y);
void rindow_matlib_common_i_add(int32_t n, int32_t dtype, void *x, void *y);
#ifdef __cplusplus
} // extern "C"
#endif

// RINDOW_MATLIB_COMMON_H_
#endif
