#include <stdio.h>
#include <stdint.h>
#include <math.h>
#ifdef _MSC_VER
#include <windows.h>
#else
#include <sys/sysinfo.h>
#endif
#ifdef _OPENMP
#include <omp.h>
#endif

#define RINDOW_MATHLIB_INCLUDING_SOURCE 1
#include "../lib/mathlib.c"
//#include "../lib/mathlib.h"

//#define N 10000000
#define N 1000
static float s_array_a[N];
static double d_array_a[N];

int main()
{
    float v=0.0;
    long long iv = 0;
    for(int i=0;i<N;i++) {
        s_array_a[i] = v;
        d_array_a[i] = (double)v;
        iv += (long long)v;
        v += 1.0;
    }
#ifndef _MSC_VER
    printf("get_nprocs_conf() = %d\n",get_nprocs_conf());
    printf("get_nprocs() = %d\n",get_nprocs());
#endif

#ifdef _OPENMP
    //printf("omp stack size=%d\n",omp_get_stack_size());
    printf("omp max threads=%d\n",omp_get_max_threads());
    printf("omp in parallel=%d\n",omp_in_parallel());
    printf("omp num threads=%d\n",omp_get_num_threads());
#endif

    printf("MAXI=%lld max 32 bit integer\n",(long long)1<<31);
    printf("MAXS=%lld max 24 bit integer\n",(long long)1<<24);
    printf("N   =%lld\n",(long long)N);
    printf("isum=%lld\n",iv);
    float result_fs = rindow_math_mathlib_s_sum(N,s_array_a,1,0.0);
    printf("ssum=%e(%f)\n",result_fs,result_fs);
    double result_fd = rindow_math_mathlib_d_sum(N,d_array_a,1,0.0);
    printf("dsum=%le(%lf)\n",result_fd,result_fd);

    int result_s = rindow_math_mathlib_s_imax(N,s_array_a,1,-INFINITY);
    printf("simax=%d\n",result_s);
    int result_d = rindow_math_mathlib_d_imax(N,d_array_a,1,-INFINITY);
    printf("dimax=%d\n",result_d);
 
#ifdef _OPENMP
    printf("omp in parallel=%d\n",omp_in_parallel());
    printf("omp num threads=%d\n",omp_get_num_threads());
#endif
    printf("Finish!");
}