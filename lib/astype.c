#include "matlib.h"
#include <math.h>

int32_t rindow_matlib_astype(
    int32_t n, int32_t from_dtype, void *x, int32_t incX, int32_t to_dtype, void *y, int32_t incY)
{
    int32_t errcode = 0;
    if(rindow_matlib_common_dtype_is_int(to_dtype) || rindow_matlib_common_dtype_is_bool(to_dtype)) {
        int64_t value;
        int32_t i;
        #pragma omp parallel for
        for(i=0;i<n;i++) {
            if(rindow_matlib_common_get_integer(from_dtype, x, incX, i, &value)) {
                errcode = -1;
            } else {
                rindow_matlib_common_set_integer(to_dtype, y, incY, i, value);
            }
        }
    } else if(rindow_matlib_common_dtype_is_float(to_dtype)) {
        double value;
        int32_t i;
        #pragma omp parallel for
        for(i=0;i<n;i++) {
            if(rindow_matlib_common_get_float(from_dtype, x, incX, i, &value)) {
                errcode = -1;
            }
            rindow_matlib_common_set_float(to_dtype, y, incY, i, value);
        }
    } else {
        errcode = -1;
    }

    return errcode;
}
