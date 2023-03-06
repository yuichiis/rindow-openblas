#ifndef RINDOW_MATH_MATHLIB_H_
#define RINDOW_MATH_MATHLIB_H_

#if !defined(RINDOW_FUNC)
  #if defined(RINDOW_COMPILING_DLL)
    #define RINDOW_FUNC
    #define RINDOW_FUNC_DECL extern __declspec(dllexport)
  #elif defined(RINDOW_MATHLIB_INCLUDING_SOURCE)
    #define RINDOW_FUNC
    #define RINDOW_FUNC_DECL static
  #else
    #define RINDOW_FUNC
    #define RINDOW_FUNC_DECL extern __declspec(dllimport)
  #endif
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

RINDOW_FUNC_DECL void rindow_math_mathlib_s_increment(int32_t n, float *x, int32_t incX, float alpha, float beta);
RINDOW_FUNC_DECL void rindow_math_mathlib_d_increment(int32_t n, double *x, int32_t incX, double alpha, double beta);
RINDOW_FUNC_DECL float rindow_math_mathlib_s_sum(int32_t n,float *x,int32_t incX, float sum);
RINDOW_FUNC_DECL double rindow_math_mathlib_d_sum(int32_t n,double *x,int32_t incX, double sum);


#ifdef __cplusplus
} // extern "C"
#endif

// RINDOW_MATH_MATHLIB_H_
#endif
