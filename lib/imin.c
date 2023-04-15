#include "matlib.h"
#include <math.h>

int32_t rindow_matlib_s_imin(int32_t n,float *x, int32_t incX, float floatMin)
{
    int32_t resultIdx = -1;
    #pragma omp parallel
    {
        int32_t i;
        float minVal=floatMin;
        int32_t minIdx=-1;
        #pragma omp for
        for(i=0; i<n; i++) {
            if(minVal>x[i*incX]) {
                minVal = x[i*incX];
                minIdx = i;
            }
        }
        #pragma omp critical
        {
            if(floatMin>minVal) {
                floatMin = minVal;
                resultIdx = minIdx;
            }
        }
    }
    return resultIdx;
}

int32_t rindow_matlib_d_imin(int32_t n,double *x, int32_t incX, double floatMin)
{
    int32_t resultIdx = -1;
    #pragma omp parallel
    {
        int32_t i;
        double minVal=floatMin;
        int32_t minIdx=-1;
        #pragma omp for
        for(i=0; i<n; i++) {
            if(minVal>x[i*incX]) {
                minVal = x[i*incX];
                minIdx = i;
            }
        }
        #pragma omp critical
        {
            if(floatMin>minVal) {
                floatMin = minVal;
                resultIdx = minIdx;
            }
        }
    }
    return resultIdx;
}

