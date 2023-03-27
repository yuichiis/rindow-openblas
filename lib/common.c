#include "mathlib.h"
#include <math.h>

#define PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(data_type) { \
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
int php_rindow_mathlib_copysub(
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
        case rindow_math_mathlib_dtype_float32:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(float)
            break;
        case rindow_math_mathlib_dtype_float64:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(double)
            break;
        case rindow_math_mathlib_dtype_bool:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(int8_t)
            break;
        case rindow_math_mathlib_dtype_int8:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(int8_t)
            break;
        case rindow_math_mathlib_dtype_uint8:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(uint8_t)
            break;
        case rindow_math_mathlib_dtype_int16:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(int16_t)
            break;
        case rindow_math_mathlib_dtype_uint16:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(uint16_t)
            break;
        case rindow_math_mathlib_dtype_int32:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(int32_t)
            break;
        case rindow_math_mathlib_dtype_uint32:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(uint32_t)
            break;
        case rindow_math_mathlib_dtype_int64:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(int64_t)
            break;
        case rindow_math_mathlib_dtype_uint64:
            PHP_RINDOW_MATHLIB_COPYSUB_TEMPLATE(uint64_t)
            break;
        default:
            return -1;
    }
    return 0;
}

