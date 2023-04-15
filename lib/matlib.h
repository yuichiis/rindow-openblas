#ifndef RINDOW_MATLIB_H_
#define RINDOW_MATLIB_H_

#include <stdint.h>
#include <math.h>

#ifndef _OPENMP
    #ifdef _MSC_VER
      #include <sysinfoapi.h>
    #else
      #include <sys/sysinfo.h>
      #include <pthread.h>
    #endif
    #include <stdlib.h>
    #include <memory.h>
#endif

#ifdef _OPENMP
#include <omp.h>
#endif

enum rindow_matlib_dtype {
    rindow_matlib_dtype_unknown = 0,
    rindow_matlib_dtype_bool    = 1,
    rindow_matlib_dtype_int8    = 2,
    rindow_matlib_dtype_int16   = 3,
    rindow_matlib_dtype_int32   = 4,
    rindow_matlib_dtype_int64   = 5,
    rindow_matlib_dtype_uint8   = 6,
    rindow_matlib_dtype_uint16  = 7,
    rindow_matlib_dtype_uint32  = 8,
    rindow_matlib_dtype_uint64  = 9,
    rindow_matlib_dtype_float8  = 10,
    rindow_matlib_dtype_float16 = 11,
    rindow_matlib_dtype_float32 = 12,
    rindow_matlib_dtype_float64 = 13,
};


#if _MSC_VER
  #if !defined(RINDOW_FUNC)
    #if defined(RINDOW_COMPILING_DLL)
      #define RINDOW_FUNC
      #define RINDOW_FUNC_DECL extern __declspec(dllexport)
    #elif defined(RINDOW_MATLIB_INCLUDING_SOURCE)
      #define RINDOW_FUNC
      #define RINDOW_FUNC_DECL
    #else
      #define RINDOW_FUNC
      #define RINDOW_FUNC_DECL extern __declspec(dllimport)
    #endif
  #endif
#else // _MSC_VER
  #define RINDOW_FUNC
  #define RINDOW_FUNC_DECL extern
#endif // _MSC_VER

#ifndef _OPENMP
typedef struct _arg_s_sum_kernel {
  #ifdef _MSC_VER
    int64_t tid;
  #else
    pthread_t tid;
  #endif
    float sum;
    int32_t n;
    float *x;
    int32_t incX;
} arg_s_sum_kernel_t;
typedef struct _arg_d_sum_kernel {
  #ifdef _MSC_VER
    int64_t tid;
  #else
    pthread_t tid;
  #endif
    double sum;
    int32_t n;
    double *x;
    int32_t incX;
} arg_d_sum_kernel_t;

#ifdef _MSC_VER
int get_nprocs(void)
{
  static int nums = 0;
  if (nums == 0) {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    nums = sysinfo.dwNumberOfProcessors;
  }
  return nums;
}
#endif // _MSC_VER

#endif // ifndef _OPENMP


#define RINDOW_MATLIB_SUCCESS                0
#define RINDOW_MATLIB_E_MEM_ALLOC_FAILURE -101
#define RINDOW_MATLIB_E_PERM_OUT_OF_RANGE -102
#define RINDOW_MATLIB_E_DUP_AXIS          -103

static inline int32_t php_rindow_matlib_common_dtype_to_valuesize(int32_t dtype)
{
    switch (dtype) {
        case rindow_matlib_dtype_bool:
        case rindow_matlib_dtype_int8:
        case rindow_matlib_dtype_uint8:
        case rindow_matlib_dtype_float8:
            return 1;
        case rindow_matlib_dtype_int16:
        case rindow_matlib_dtype_uint16:
        case rindow_matlib_dtype_float16:
            return 2;
        case rindow_matlib_dtype_int32:
        case rindow_matlib_dtype_uint32:
        case rindow_matlib_dtype_float32:
            return 4;
        case rindow_matlib_dtype_int64:
        case rindow_matlib_dtype_uint64:
        case rindow_matlib_dtype_float64:
            return 8;
    }
    return 0;
}



#ifdef __cplusplus
extern "C" {
#endif

RINDOW_FUNC_DECL float rindow_matlib_s_sum(int32_t n,float *x,int32_t incX, float sum);
RINDOW_FUNC_DECL double rindow_matlib_d_sum(int32_t n,double *x,int32_t incX, double sum);
RINDOW_FUNC_DECL int64_t rindow_matlib_int_sum(int32_t dtype, int32_t n,void *x,int32_t incX, int64_t sum);
RINDOW_FUNC_DECL int32_t rindow_matlib_s_imax(int32_t n,float *x, int32_t incX, float floatMax);
RINDOW_FUNC_DECL int32_t rindow_matlib_d_imax(int32_t n,double *x, int32_t incX, double floatMax);
RINDOW_FUNC_DECL int32_t rindow_matlib_s_imin(int32_t n,float *x, int32_t incX, float floatMin);
RINDOW_FUNC_DECL int32_t rindow_matlib_d_imin(int32_t n,double *x, int32_t incX, double floatMin);
RINDOW_FUNC_DECL void rindow_matlib_s_increment(int32_t n, float *x, int32_t incX, float alpha, float beta);
RINDOW_FUNC_DECL void rindow_matlib_d_increment(int32_t n, double *x, int32_t incX, double alpha, double beta);
RINDOW_FUNC_DECL void rindow_matlib_s_reciprocal(int32_t n, float *x, int32_t incX, float alpha, float beta);
RINDOW_FUNC_DECL void rindow_matlib_d_reciprocal(int32_t n, double *x, int32_t incX, double alpha, double beta);
RINDOW_FUNC_DECL void rindow_matlib_s_maximum(int32_t m,int32_t n,float *a, int32_t ldA,float *x, int32_t incX);
RINDOW_FUNC_DECL void rindow_matlib_d_maximum(int32_t m,int32_t n,double *a, int32_t ldA,double *x, int32_t incX);
RINDOW_FUNC_DECL void rindow_matlib_s_minimum(int32_t m,int32_t n,float *a, int32_t ldA,float *x, int32_t incX);
RINDOW_FUNC_DECL void rindow_matlib_d_minimum(int32_t m,int32_t n,double *a, int32_t ldA,double *x, int32_t incX);
RINDOW_FUNC_DECL int32_t rindow_matlib_s_transpose(int32_t ndim,int32_t *shape,int32_t *perm,float *a,float *b);
RINDOW_FUNC_DECL int32_t rindow_matlib_d_transpose(int32_t ndim,int32_t *shape,int32_t *perm,double *a,double *b);
RINDOW_FUNC_DECL int32_t rindow_matlib_int_transpose(int32_t dtype,int32_t ndim,int32_t *shape,int32_t *perm,void *a,void *b);
RINDOW_FUNC_DECL void rindow_matlib_s_bandpart(int32_t m, int32_t n, int32_t k,float *a,int32_t lower, int32_t upper);
RINDOW_FUNC_DECL void rindow_matlib_d_bandpart(int32_t m, int32_t n, int32_t k,double *a,int32_t lower, int32_t upper);


#ifdef __cplusplus
} // extern "C"
#endif

// RINDOW_MATLIB_H_
#endif

