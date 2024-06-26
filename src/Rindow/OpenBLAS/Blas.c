#include <php.h>
#include <Zend/zend_interfaces.h>
#include <Zend/zend_exceptions.h>
#include <ext/spl/spl_iterators.h>
#include <ext/spl/spl_exceptions.h>
#include <cblas.h>
#include <Interop/Polite/Math/Matrix.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_rindow_openblas.h"


static zend_object_handlers rindow_openblas_blas_object_handlers;

// destractor
static void php_rindow_openblas_blas_free_object(zend_object* object)
{
    zend_object_std_dtor(object);
}

// constructor
static zend_object* php_rindow_openblas_blas_create_object(zend_class_entry* class_type) /* {{{ */
{
    zend_object* intern = NULL;

    intern = (zend_object*)ecalloc(1, sizeof(zend_object) + zend_object_properties_size(class_type));

    zend_object_std_init(intern, class_type);
    object_properties_init(intern, class_type);

    intern->handlers = &rindow_openblas_blas_object_handlers;

    return intern;
} /* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function getNumThreads() : int
 {{{ */
static PHP_METHOD(Blas, getNumThreads)
{
    zend_long n;
    n = (zend_long)openblas_get_num_threads();
    RETURN_LONG(n);
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function getNumProcs() : int
 {{{ */
static PHP_METHOD(Blas, getNumProcs)
{
    zend_long n;
    n = (zend_long)openblas_get_num_procs();
    RETURN_LONG(n);
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function getConfig() : string
 {{{ */
static PHP_METHOD(Blas, getConfig)
{
    char *s;
    s = openblas_get_config();
    RETURN_STRING(s);
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function getCorename() : string
 {{{ */
static PHP_METHOD(Blas, getCorename)
{
    char *s;
    s = openblas_get_corename();
    RETURN_STRING(s);
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function getParallel() : int
 {{{ */
static PHP_METHOD(Blas, getParallel)
{
    zend_long n;
    n = (zend_long)openblas_get_parallel();
    RETURN_LONG(n);
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function scal(
        int $n,
        float $alpha,
        Buffer $X, int $offsetX, int $incX) : void
 {{{ */
static PHP_METHOD(Blas, scal)
{
    php_interop_polite_math_matrix_linear_buffer_t* buffer;
    zend_long n;
    double alpha;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 5, 5)
        Z_PARAM_LONG(n)
        Z_PARAM_DOUBLE(alpha)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
    ZEND_PARSE_PARAMETERS_END();

    buffer = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(buffer,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", buffer,n,offsetX,incX)) {
        return;
    }
    switch (buffer->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_sscal((blasint)n, (float)alpha, &(((float *)buffer->data)[offsetX]), (blasint)incX);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dscal((blasint)n, (double)alpha, &(((double *)buffer->data)[offsetX]), (blasint)incX);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function axpy(
        int $n,
        float $alpha,
        Buffer $X, int $offsetX, int $incX,
        Buffer $Y, int $offsetY, int $incY ) : void
 {{{ */
static PHP_METHOD(Blas, axpy)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferX;
    php_interop_polite_math_matrix_linear_buffer_t* bufferY;
    zend_long n;
    double alpha;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    zval* y=NULL;
    zend_long offsetY;
    zend_long incY;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 8, 8)
        Z_PARAM_LONG(n)
        Z_PARAM_DOUBLE(alpha)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
        Z_PARAM_OBJECT(y) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetY)
        Z_PARAM_LONG(incY)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer X
    bufferX = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(bufferX,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", bufferX,n,offsetX,incX)) {
        return;
    }

    // Check Buffer Y
    bufferY = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(y);
    if(php_rindow_openblas_assert_buffer_type(bufferY,"y")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "Y", bufferY,n,offsetY,incY)) {
        return;
    }

    // Check Buffer X and Y
    if(bufferX->dtype!=bufferY->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for X and Y", 0);
        return;
    }

    switch (bufferX->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_saxpy((blasint)n, (float)alpha,
                &(((float *)bufferX->data)[offsetX]), (blasint)incX,
                &(((float *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_daxpy((blasint)n, (double)alpha,
                &(((double *)bufferX->data)[offsetX]), (blasint)incX,
                &(((double *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function dot(
        int $n,
        Buffer $X, int $offsetX, int $incX,
        Buffer $Y, int $offsetY, int $incY ) : float
 {{{ */
static PHP_METHOD(Blas, dot)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferX;
    php_interop_polite_math_matrix_linear_buffer_t* bufferY;
    zend_long n;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    zval* y=NULL;
    zend_long offsetY;
    zend_long incY;
    double result;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 7, 7)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
        Z_PARAM_OBJECT(y) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetY)
        Z_PARAM_LONG(incY)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer X
    bufferX = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(bufferX,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", bufferX,n,offsetX,incX)) {
        return;
    }

    // Check Buffer Y
    bufferY = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(y);
    if(php_rindow_openblas_assert_buffer_type(bufferY,"y")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "Y", bufferY,n,offsetY,incY)) {
        return;
    }

    // Check Buffer X and Y
    if(bufferX->dtype!=bufferY->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for X and Y", 0);
        return;
    }

    switch (bufferX->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            result = (double)cblas_sdot((blasint)n,
                &(((float *)bufferX->data)[offsetX]), (blasint)incX,
                &(((float *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            result = (double)cblas_ddot((blasint)n,
                &(((double *)bufferX->data)[offsetX]), (blasint)incX,
                &(((double *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
    RETURN_DOUBLE(result);
}
/* }}} */


/* Method Rindow\OpenBLAS\Blas::
    public function asum(
        int $n,
        Buffer $X, int $offsetX, int $incX ) : float
 {{{ */
static PHP_METHOD(Blas, asum)
{
    php_interop_polite_math_matrix_linear_buffer_t* buffer;
    zend_long n;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    double result;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 4, 4)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    buffer = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(buffer,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", buffer,n,offsetX,incX)) {
        return;
    }
    switch (buffer->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            result = (double)cblas_sasum((blasint)n, &(((float *)buffer->data)[offsetX]), (blasint)incX);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            result = (double)cblas_dasum((blasint)n, &(((double *)buffer->data)[offsetX]), (blasint)incX);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
    RETURN_DOUBLE(result);
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function iamax(
        int $n,
        Buffer $X, int $offsetX, int $incX ) : int
 {{{ */
static PHP_METHOD(Blas, iamax)
{
    php_interop_polite_math_matrix_linear_buffer_t* buffer;
    zend_long n;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    zend_long resultIdx;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 4, 4)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    buffer = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(buffer,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", buffer,n,offsetX,incX)) {
        return;
    }
    switch (buffer->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            resultIdx = (zend_long)cblas_isamax((blasint)n, &(((float *)buffer->data)[offsetX]), (blasint)incX);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            resultIdx = (zend_long)cblas_idamax((blasint)n, &(((double *)buffer->data)[offsetX]), (blasint)incX);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
    RETURN_LONG(resultIdx);
}
/* }}} */

#ifdef OPENBLAS_HAVE_IAMIN
/* Method Rindow\OpenBLAS\Blas::
    public function iamin(
        int $n,
        Buffer $X, int $offsetX, int $incX ) : int
 {{{ */
static PHP_METHOD(Blas, iamin)
{
    php_interop_polite_math_matrix_linear_buffer_t* buffer;
    zend_long n;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    zend_long resultIdx;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 4, 4)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    buffer = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(buffer,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", buffer,n,offsetX,incX)) {
        return;
    }
    switch (buffer->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            resultIdx = (zend_long)cblas_isamin((blasint)n, &(((float *)buffer->data)[offsetX]), (blasint)incX);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            resultIdx = (zend_long)cblas_idamin((blasint)n, &(((double *)buffer->data)[offsetX]), (blasint)incX);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
    RETURN_LONG(resultIdx);
}
/* }}} */
#endif

/* Method Rindow\OpenBLAS\Blas::
    public function copy(
        int $n,
        Buffer $X, int $offsetX, int $incX,
        Buffer $Y, int $offsetY, int $incY ) : void
 {{{ */
static PHP_METHOD(Blas, copy)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferX;
    php_interop_polite_math_matrix_linear_buffer_t* bufferY;
    zend_long n;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    zval* y=NULL;
    zend_long offsetY;
    zend_long incY;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 7, 7)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
        Z_PARAM_OBJECT(y) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetY)
        Z_PARAM_LONG(incY)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer X
    bufferX = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(bufferX,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", bufferX,n,offsetX,incX)) {
        return;
    }

    // Check Buffer Y
    bufferY = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(y);
    if(php_rindow_openblas_assert_buffer_type(bufferY,"y")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "Y", bufferY,n,offsetY,incY)) {
        return;
    }

    // Check Buffer X and Y
    if(bufferX->dtype!=bufferY->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for X and Y", 0);
        return;
    }

    switch (bufferX->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_scopy((blasint)n,
                &(((float *)bufferX->data)[offsetX]), (blasint)incX,
                &(((float *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dcopy((blasint)n,
                &(((double *)bufferX->data)[offsetX]), (blasint)incX,
                &(((double *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        default:
            {
                zend_long i,idX,idY;
                int valueSize;
                uint8_t *x,*y;
                valueSize = php_rindow_openblas_common_dtype_to_valuesize(bufferX->dtype);
                x = php_rindow_openblas_get_address(bufferX,offsetX,valueSize);
                y = php_rindow_openblas_get_address(bufferY,offsetY,valueSize);
                if(incX==1 && incY==1) {
                    memcpy(y,x,valueSize*n);
                } else {
                    for(i=0,idX=0,idY=0; i<n; i++,idX+=incX,idY+=incY) {
                        memcpy(&y[valueSize*idY],&x[valueSize*idX],valueSize);
                    }
                }
            }
            break;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function nrm2(
        int $n,
        Buffer $X, int $offsetX, int $incX ) : float
 {{{ */
static PHP_METHOD(Blas, nrm2)
{
    php_interop_polite_math_matrix_linear_buffer_t* buffer;
    zend_long n;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    double result;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 4, 4)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    buffer = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(buffer,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", buffer,n,offsetX,incX)) {
        return;
    }
    switch (buffer->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            result = (double)cblas_snrm2((blasint)n, &(((float *)buffer->data)[offsetX]), (blasint)incX);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            result = (double)cblas_dnrm2((blasint)n, &(((double *)buffer->data)[offsetX]), (blasint)incX);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
    RETURN_DOUBLE(result);
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function rotg(
        Buffer $A, int $offsetA,
        Buffer $B, int $offsetB,
        Buffer $C, int $offsetC,
        Buffer $S, int $offsetS,
    ) : void
 {{{ */
static PHP_METHOD(Blas, rotg)
{
    zval* a;
    zend_long offsetA;
    zval* b;
    zend_long offsetB;
    zval* c;
    zend_long offsetC;
    zval* s;
    zend_long offsetS;
    php_interop_polite_math_matrix_linear_buffer_t* bufferA;
    php_interop_polite_math_matrix_linear_buffer_t* bufferB;
    php_interop_polite_math_matrix_linear_buffer_t* bufferC;
    php_interop_polite_math_matrix_linear_buffer_t* bufferS;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 8, 8)
        Z_PARAM_OBJECT(a) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetA)
        Z_PARAM_OBJECT(b) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetB)
        Z_PARAM_OBJECT(c) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetC)
        Z_PARAM_OBJECT(s) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetS)
    ZEND_PARSE_PARAMETERS_END();

    // Check Buffer A
    bufferA = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_buffer_type(bufferA,"a")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", bufferA,1,offsetA,1)) {
        return;
    }

    // Check Buffer B
    bufferB = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(b);
    if(php_rindow_openblas_assert_buffer_type(bufferB,"b")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "Y", bufferB,1,offsetB,1)) {
        return;
    }

    // Check Buffer C
    bufferC = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(c);
    if(php_rindow_openblas_assert_buffer_type(bufferC,"c")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", bufferC,1,offsetC,1)) {
        return;
    }

    // Check Buffer S
    bufferS = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(s);
    if(php_rindow_openblas_assert_buffer_type(bufferS,"s")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "Y", bufferS,1,offsetS,1)) {
        return;
    }


    // Check Buffer A and B and C and S
    if(bufferA->dtype!=bufferB->dtype || bufferB->dtype!=bufferC->dtype ||
        bufferC->dtype!=bufferS->dtype || bufferS->dtype!=bufferA->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A,B,C and S", 0);
        return;
    }

    switch (bufferA->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_srotg(
                &(((float *)bufferA->data)[offsetA]),
                &(((float *)bufferB->data)[offsetB]),
                &(((float *)bufferC->data)[offsetC]),
                &(((float *)bufferS->data)[offsetS])
            );
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_drotg(
                &(((double *)bufferA->data)[offsetA]),
                &(((double *)bufferB->data)[offsetB]),
                &(((double *)bufferC->data)[offsetC]),
                &(((double *)bufferS->data)[offsetS])
            );
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function rot(
        int $n,
        Buffer $X, int $offsetX, int $incX,
        Buffer $Y, int $offsetY, int $incY,
        Buffer $C, int $offsetC,
        Buffer $S, int $offsetS,
    ) : void
 {{{ */
static PHP_METHOD(Blas, rot)
{
    zend_long n;
    zval* x;
    zend_long offsetX;
    zend_long incX;
    zval* y;
    zend_long offsetY;
    zend_long incY;
    zval* c;
    zend_long offsetC;
    zval* s;
    zend_long offsetS;
    php_interop_polite_math_matrix_linear_buffer_t* bufferX;
    php_interop_polite_math_matrix_linear_buffer_t* bufferY;
    php_interop_polite_math_matrix_linear_buffer_t* bufferC;
    php_interop_polite_math_matrix_linear_buffer_t* bufferS;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 11, 11)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
        Z_PARAM_OBJECT(y) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetY)
        Z_PARAM_LONG(incY)
        Z_PARAM_OBJECT(c) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetC)
        Z_PARAM_OBJECT(s) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetS)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer X
    bufferX = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(bufferX,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", bufferX,n,offsetX,incX)) {
        return;
    }

    // Check Buffer Y
    bufferY = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(y);
    if(php_rindow_openblas_assert_buffer_type(bufferY,"y")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "Y", bufferY,n,offsetY,incY)) {
        return;
    }

    // Check Buffer C
    bufferC = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(c);
    if(php_rindow_openblas_assert_buffer_type(bufferC,"c")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", bufferC,1,offsetC,1)) {
        return;
    }

    // Check Buffer S
    bufferS = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(s);
    if(php_rindow_openblas_assert_buffer_type(bufferS,"s")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "Y", bufferS,1,offsetS,1)) {
        return;
    }

    // Check Buffer X and Y
    if(bufferX->dtype!=bufferY->dtype||bufferY->dtype!=bufferC->dtype||
        bufferC->dtype!=bufferS->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for X,Y,C and S", 0);
        return;
    }

    switch (bufferX->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_srot((blasint)n,
                &(((float *)bufferX->data)[offsetX]), (blasint)incX,
                &(((float *)bufferY->data)[offsetY]), (blasint)incY,
                ((float *)bufferC->data)[offsetC],
                ((float *)bufferS->data)[offsetS]
            );
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_drot((blasint)n,
                &(((double *)bufferX->data)[offsetX]), (blasint)incX,
                &(((double *)bufferY->data)[offsetY]), (blasint)incY,
                ((double *)bufferC->data)[offsetC],
                ((double *)bufferS->data)[offsetS]
            );
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function rotmg(
        Buffer $D1, int $offsetD1,
        Buffer $D2, int $offsetD2,
        Buffer $B1, int $offsetB1,
        Buffer $B2, int $offsetB2,
        Buffer $P, int $offsetP
        ) : void
 {{{ */
static PHP_METHOD(Blas, rotmg)
{
    zval* d1;
    zend_long offsetD1;
    zval* d2;
    zend_long offsetD2;
    zval* b1;
    zend_long offsetB1;
    zval* b2;
    zend_long offsetB2;
    zval* p;
    zend_long offsetP;
    php_interop_polite_math_matrix_linear_buffer_t* bufferD1;
    php_interop_polite_math_matrix_linear_buffer_t* bufferD2;
    php_interop_polite_math_matrix_linear_buffer_t* bufferB1;
    php_interop_polite_math_matrix_linear_buffer_t* bufferB2;
    php_interop_polite_math_matrix_linear_buffer_t* bufferP;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 10, 10)
        Z_PARAM_OBJECT(d1) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetD1)
        Z_PARAM_OBJECT(d2) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetD2)
        Z_PARAM_OBJECT(b1) // Interop\Polite\Math\Matrix\LinearBuffer

        Z_PARAM_LONG(offsetB1)
        Z_PARAM_OBJECT(b2) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetB2)
        Z_PARAM_OBJECT(p) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetP)
    ZEND_PARSE_PARAMETERS_END();

    // Check Buffer D1
    bufferD1 = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(d1);
    if(php_rindow_openblas_assert_buffer_type(bufferD1,"d1")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "D1", bufferD1,1,offsetD1,1)) {
        return;
    }

    // Check Buffer D2
    bufferD2 = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(d2);
    if(php_rindow_openblas_assert_buffer_type(bufferD2,"d2")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "D2", bufferD2,1,offsetD2,1)) {
        return;
    }

    // Check Buffer B1
    bufferB1 = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(b1);
    if(php_rindow_openblas_assert_buffer_type(bufferB1,"b1")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "B1", bufferB1,1,offsetB1,1)) {
        return;
    }

    // Check Buffer B2
    bufferB2 = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(b2);
    if(php_rindow_openblas_assert_buffer_type(bufferB2,"b2")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "B2", bufferB2,1,offsetB2,1)) {
        return;
    }

    // Check Buffer P
    bufferP = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(p);
    if(php_rindow_openblas_assert_buffer_type(bufferP,"p")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "P", bufferP,5,offsetP,1)) {
        return;
    }

    // Check Buffer D1 and D2 and B1 and B2 and P
    if(bufferD1->dtype!=bufferD2->dtype || bufferD1->dtype!=bufferB1->dtype ||
        bufferD1->dtype!=bufferB2->dtype || bufferD1->dtype!=bufferP->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for D1,D2,B1,B2 and P", 0);
        return;
    }

    switch (bufferD1->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_srotmg(
                &(((float *)bufferD1->data)[offsetD1]),
                &(((float *)bufferD2->data)[offsetD2]),
                &(((float *)bufferB1->data)[offsetB1]),
                ((float *)bufferB2->data)[offsetB2],
                &(((float *)bufferP->data)[offsetP])
            );
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_drotmg(
                &(((double *)bufferD1->data)[offsetD1]),
                &(((double *)bufferD2->data)[offsetD2]),
                &(((double *)bufferB1->data)[offsetB1]),
                ((double *)bufferB2->data)[offsetB2],
                &(((double *)bufferP->data)[offsetP])
            );
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function rotm(
        int $N,
        Buffer $X, int $offsetX, int $incX,
        Buffer $Y, int $offsetY, int $incY,
        Buffer $P, int $offsetP
        ) : void
 {{{ */
static PHP_METHOD(Blas, rotm)
{
    zend_long n;
    zval* x;
    zend_long offsetX;
    zend_long incX;
    zval* y;
    zend_long offsetY;
    zend_long incY;
    zval* p;
    zend_long offsetP;
    php_interop_polite_math_matrix_linear_buffer_t* bufferX;
    php_interop_polite_math_matrix_linear_buffer_t* bufferY;
    php_interop_polite_math_matrix_linear_buffer_t* bufferP;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 9, 9)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
        Z_PARAM_OBJECT(y) // Interop\Polite\Math\Matrix\LinearBuffer

        Z_PARAM_LONG(offsetY)
        Z_PARAM_LONG(incY)
        Z_PARAM_OBJECT(p) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetP)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer X
    bufferX = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(bufferX,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", bufferX,n,offsetX,incX)) {
        return;
    }

    // Check Buffer Y
    bufferY = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(y);
    if(php_rindow_openblas_assert_buffer_type(bufferY,"y")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "Y", bufferY,n,offsetY,incY)) {
        return;
    }

    // Check Buffer P
    bufferP = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(p);
    if(php_rindow_openblas_assert_buffer_type(bufferP,"p")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "P", bufferP,5,offsetP,1)) {
        return;
    }

    // Check Buffer X and Y
    if(bufferX->dtype!=bufferY->dtype||bufferX->dtype!=bufferP->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for X,Y and P", 0);
        return;
    }

    switch (bufferX->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_srotm((blasint)n,
                &(((float *)bufferX->data)[offsetX]), (blasint)incX,
                &(((float *)bufferY->data)[offsetY]), (blasint)incY,
                &(((float *)bufferP->data)[offsetY])
            );
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_drotm((blasint)n,
                &(((double *)bufferX->data)[offsetX]), (blasint)incX,
                &(((double *)bufferY->data)[offsetY]), (blasint)incY,
                &(((double *)bufferP->data)[offsetY])
            );
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function swap(
        int $n,
        Buffer $X, int $offsetX, int $incX,
        Buffer $Y, int $offsetY, int $incY ) : void
 {{{ */
static PHP_METHOD(Blas, swap)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferX;
    php_interop_polite_math_matrix_linear_buffer_t* bufferY;
    zend_long n;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    zval* y=NULL;
    zend_long offsetY;
    zend_long incY;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 7, 7)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
        Z_PARAM_OBJECT(y) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetY)
        Z_PARAM_LONG(incY)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer X
    bufferX = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(bufferX,"x")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "X", bufferX,n,offsetX,incX)) {
        return;
    }

    // Check Buffer Y
    bufferY = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(y);
    if(php_rindow_openblas_assert_buffer_type(bufferY,"y")) {
        return;
    }
    if(php_rindow_openblas_assert_vector_buffer_spec(
        "Y", bufferY,n,offsetY,incY)) {
        return;
    }

    // Check Buffer X and Y
    if(bufferX->dtype!=bufferY->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for X and Y", 0);
        return;
    }

    switch (bufferX->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_sswap((blasint)n,
                &(((float *)bufferX->data)[offsetX]), (blasint)incX,
                &(((float *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dswap((blasint)n,
                &(((double *)bufferX->data)[offsetX]), (blasint)incX,
                &(((double *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function gemv(
        int $order,
        int $trans,
        int $m,
        int $n,
        float $alpha,
        Buffer $A, int $offsetA, int $ldA,
        Buffer $X, int $offsetX, int $incX,
        float $beta,
        Buffer $Y, int $offsetY, int $incY ) : void
 {{{ */
static PHP_METHOD(Blas, gemv)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferA;
    php_interop_polite_math_matrix_linear_buffer_t* bufferX;
    php_interop_polite_math_matrix_linear_buffer_t* bufferY;
    zend_long order;
    zend_long trans;
    zend_long m;
    zend_long n;
    double alpha;
    zval* a=NULL;
    zend_long offsetA;
    zend_long ldA;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    double beta;
    zval* y=NULL;
    zend_long offsetY;
    zend_long incY;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 15, 15)
        Z_PARAM_LONG(order)
        Z_PARAM_LONG(trans)
        Z_PARAM_LONG(m)
        Z_PARAM_LONG(n)
        Z_PARAM_DOUBLE(alpha)
        Z_PARAM_OBJECT(a) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetA)
        Z_PARAM_LONG(ldA)
        Z_PARAM_OBJECT(x) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
        Z_PARAM_DOUBLE(beta)
        Z_PARAM_OBJECT(y) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetY)
        Z_PARAM_LONG(incY)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "m", m)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer A
    bufferA = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_buffer_type(bufferA,"a")) {
        return;
    }
    if(php_rindow_openblas_assert_matrix_buffer_spec(
        "A", bufferA,m,n,offsetA,ldA)) {
        return;
    }

    // Check Buffer X
    bufferX = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_buffer_type(bufferX,"x")) {
        return;
    }

    // Check Buffer Y
    bufferY = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(y);
    if(php_rindow_openblas_assert_buffer_type(bufferY,"y")) {
        return;
    }

    // Check Buffer size X and Y
    {
        zend_long rows,cols;
        if(trans==CblasNoTrans || trans==CblasConjNoTrans ) {
            rows = m; cols = n;
        } else if(trans==CblasTrans || trans==CblasConjTrans) {
            rows = n; cols = m;
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "unknown transpose mode for bufferA.", 0);
            return;
        }
        if(php_rindow_openblas_assert_vector_buffer_spec(
            "X", bufferX,cols,offsetX,incX)) {
            return;
        }
        if(php_rindow_openblas_assert_vector_buffer_spec(
            "Y", bufferY,rows,offsetY,incY)) {
            return;
        }
    }

    // Check Buffer A and X and Y
    if(bufferA->dtype!=bufferX->dtype || bufferX->dtype!=bufferY->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A and X and Y", 0);
        return;
    }

    switch (bufferX->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_sgemv(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (blasint)m,(blasint)n,
                (float)alpha,
                &(((float *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((float *)bufferX->data)[offsetX]), (blasint)incX,
                (float)beta,
                &(((float *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dgemv(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (blasint)m,(blasint)n,
                (double)alpha,
                &(((double *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((double *)bufferX->data)[offsetX]), (blasint)incX,
                (double)beta,
                &(((double *)bufferY->data)[offsetY]), (blasint)incY);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function gemm(
        int $order,
        int $transA,
        int $transB,
        int $m,
        int $n,
        int $k,
        float $alpha,
        Buffer $A, int $offsetA, int $ldA,
        Buffer $B, int $offsetB, int $ldB,
        float $beta,
        Buffer $C, int $offsetC, int $ldC ) : void
 {{{ */
static PHP_METHOD(Blas, gemm)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferA;
    php_interop_polite_math_matrix_linear_buffer_t* bufferB;
    php_interop_polite_math_matrix_linear_buffer_t* bufferC;
    zend_long order;
    zend_long transA;
    zend_long transB;
    zend_long m;
    zend_long n;
    zend_long k;
    double alpha;
    zval* a=NULL;
    zend_long offsetA;
    zend_long ldA;
    zval* b=NULL;
    zend_long offsetB;
    zend_long ldB;
    double beta;
    zval* c=NULL;
    zend_long offsetC;
    zend_long ldC;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 17, 17)
        Z_PARAM_LONG(order)
        Z_PARAM_LONG(transA)
        Z_PARAM_LONG(transB)
        Z_PARAM_LONG(m)
        Z_PARAM_LONG(n)
        Z_PARAM_LONG(k)
        Z_PARAM_DOUBLE(alpha)
        Z_PARAM_OBJECT(a) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetA)
        Z_PARAM_LONG(ldA)
        Z_PARAM_OBJECT(b) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetB)
        Z_PARAM_LONG(ldB)
        Z_PARAM_DOUBLE(beta)
        Z_PARAM_OBJECT(c) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetC)
        Z_PARAM_LONG(ldC)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "m", m)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "k", k)) {
        return;
    }
    // Check Buffer A
    bufferA = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_buffer_type(bufferA,"a")) {
        return;
    }
    {
        zend_long rows,cols;
        if(transA==CblasNoTrans || transA==CblasConjNoTrans) {
            rows = m; cols = k;
        } else if(transA==CblasTrans || transA==CblasConjTrans) {
            rows = k; cols = m;
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "unknown transpose mode for bufferA.", 0);
            return;
        }
        if(php_rindow_openblas_assert_matrix_buffer_spec(
            "A", bufferA,rows,cols,offsetA,ldA)) {
            return;
        }
    }

    // Check Buffer B
    bufferB = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(b);
    if(php_rindow_openblas_assert_buffer_type(bufferB,"b")) {
        return;
    }
    {
        zend_long rows,cols;
        if(transB==CblasNoTrans || transB==CblasConjNoTrans) {
            rows = k; cols = n;
        } else if(transB==CblasTrans || transB==CblasConjTrans) {
            rows = n; cols = k;
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "unknown transpose mode for bufferB.", 0);
            return;
        }
        if(php_rindow_openblas_assert_matrix_buffer_spec(
            "B", bufferB,rows,cols,offsetB,ldB)) {
            return;
        }
    }

    // Check Buffer C
    bufferC = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(c);
    if(php_rindow_openblas_assert_buffer_type(bufferC,"c")) {
        return;
    }
    if(php_rindow_openblas_assert_matrix_buffer_spec(
        "C", bufferC,m,n,offsetC,ldC)) {
        return;
    }

    // Check Buffer A and B and C
    if(bufferA->dtype!=bufferB->dtype || bufferB->dtype!=bufferC->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A and B and C", 0);
        return;
    }

    switch (bufferA->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_sgemm(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)transA,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)transB,
                (blasint)m,(blasint)n,(blasint)k,
                (float)alpha,
                &(((float *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((float *)bufferB->data)[offsetB]), (blasint)ldB,
                (float)beta,
                &(((float *)bufferC->data)[offsetC]), (blasint)ldC);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dgemm(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)transA,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)transB,
                (blasint)m,(blasint)n,(blasint)k,
                (double)alpha,
                &(((double *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((double *)bufferB->data)[offsetB]), (blasint)ldB,
                (double)beta,
                &(((double *)bufferC->data)[offsetC]), (blasint)ldC);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function symm(
        int $order,
        int $side,
        int $uplo,
        int $m,
        int $n,
        float $alpha,
        Buffer $A, int $offsetA, int $ldA,
        Buffer $B, int $offsetB, int $ldB,
        float $beta,
        Buffer $C, int $offsetC, int $ldC ) : void
 {{{ */
static PHP_METHOD(Blas, symm)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferA;
    php_interop_polite_math_matrix_linear_buffer_t* bufferB;
    php_interop_polite_math_matrix_linear_buffer_t* bufferC;
    zend_long order;
    zend_long side;
    zend_long uplo;
    zend_long m;
    zend_long n;
    double alpha;
    zval* a=NULL;
    zend_long offsetA;
    zend_long ldA;
    zval* b=NULL;
    zend_long offsetB;
    zend_long ldB;
    double beta;
    zval* c=NULL;
    zend_long offsetC;
    zend_long ldC;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 16, 16)
        Z_PARAM_LONG(order)
        Z_PARAM_LONG(side)
        Z_PARAM_LONG(uplo)
        Z_PARAM_LONG(m)
        Z_PARAM_LONG(n)
        Z_PARAM_DOUBLE(alpha)
        Z_PARAM_OBJECT(a) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetA)
        Z_PARAM_LONG(ldA)
        Z_PARAM_OBJECT(b) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetB)
        Z_PARAM_LONG(ldB)
        Z_PARAM_DOUBLE(beta)
        Z_PARAM_OBJECT(c) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetC)
        Z_PARAM_LONG(ldC)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "m", m)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer A
    bufferA = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_buffer_type(bufferA,"a")) {
        return;
    }
    if(!php_interop_polite_math_matrix_is_linear_buffer(bufferA)) {
        zend_throw_exception(zend_ce_type_error, "invalid type.", 0);
        return;
    }
    {
        zend_long rows;
        if(side==CblasLeft) {
            rows = m;
        } else if(side==CblasRight) {
            rows = n;
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "unknown side mode for bufferA.", 0);
            return;
        }
        if(php_rindow_openblas_assert_matrix_buffer_spec(
            "A", bufferA,rows,rows,offsetA,ldA)) {
            return;
        }
    }

    // Check Buffer B
    bufferB = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(b);
    if(php_rindow_openblas_assert_buffer_type(bufferB,"b")) {
        return;
    }
    {
        if(php_rindow_openblas_assert_matrix_buffer_spec(
            "B", bufferB,m,n,offsetB,ldB)) {
            return;
        }
    }

    // Check Buffer C
    bufferC = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(c);
    if(php_rindow_openblas_assert_buffer_type(bufferC,"c")) {
        return;
    }
    if(php_rindow_openblas_assert_matrix_buffer_spec(
        "C", bufferC,m,n,offsetC,ldC)) {
        return;
    }

    // Check Buffer A and B and C
    if(bufferA->dtype!=bufferB->dtype || bufferB->dtype!=bufferC->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A and B and C", 0);
        return;
    }

    switch (bufferA->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_ssymm(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_SIDE)side,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (blasint)m,(blasint)n,
                (float)alpha,
                &(((float *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((float *)bufferB->data)[offsetB]), (blasint)ldB,
                (float)beta,
                &(((float *)bufferC->data)[offsetC]), (blasint)ldC);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dsymm(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_SIDE)side,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (blasint)m,(blasint)n,
                (double)alpha,
                &(((double *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((double *)bufferB->data)[offsetB]), (blasint)ldB,
                (double)beta,
                &(((double *)bufferC->data)[offsetC]), (blasint)ldC);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function syrk(
        int $order,
        int $uplo,
        int $trans,
        int $n,
        int $k,
        float $alpha,
        Buffer $A, int $offsetA, int $ldA,
        float $beta,
        Buffer $C, int $offsetC, int $ldC ) : void
 {{{ */
static PHP_METHOD(Blas, syrk)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferA;
    php_interop_polite_math_matrix_linear_buffer_t* bufferC;
    zend_long order;
    zend_long uplo;
    zend_long trans;
    zend_long n;
    zend_long k;
    double alpha;
    zval* a=NULL;
    zend_long offsetA;
    zend_long ldA;
    double beta;
    zval* c=NULL;
    zend_long offsetC;
    zend_long ldC;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 13, 13)
        Z_PARAM_LONG(order)
        Z_PARAM_LONG(uplo)
        Z_PARAM_LONG(trans)
        Z_PARAM_LONG(n)
        Z_PARAM_LONG(k)
        Z_PARAM_DOUBLE(alpha)
        Z_PARAM_OBJECT(a) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetA)
        Z_PARAM_LONG(ldA)
        Z_PARAM_DOUBLE(beta)
        Z_PARAM_OBJECT(c) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetC)
        Z_PARAM_LONG(ldC)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "k", k)) {
        return;
    }
    // Check Buffer A
    bufferA = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_buffer_type(bufferA,"a")) {
        return;
    }
    {
        zend_long rows,cols;
        if(trans==CblasNoTrans || trans==CblasConjNoTrans) {
            rows = n; cols = k;
        } else if(trans==CblasTrans || trans==CblasConjTrans) {
            rows = k; cols = n;
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "unknown transpose mode for bufferA.", 0);
            return;
        }
        if(php_rindow_openblas_assert_matrix_buffer_spec(
            "A", bufferA,rows,cols,offsetA,ldA)) {
            return;
        }
    }

    // Check Buffer C
    bufferC = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(c);
    if(php_rindow_openblas_assert_buffer_type(bufferC,"c")) {
        return;
    }
    if(php_rindow_openblas_assert_matrix_buffer_spec(
        "C", bufferC,n,n,offsetC,ldC)) {
        return;
    }

    // Check Buffer A and C
    if(bufferA->dtype!=bufferC->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A and C", 0);
        return;
    }

    switch (bufferA->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_ssyrk(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (blasint)n,(blasint)k,
                (float)alpha,
                &(((float *)bufferA->data)[offsetA]), (blasint)ldA,
                (float)beta,
                &(((float *)bufferC->data)[offsetC]), (blasint)ldC);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dsyrk(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (blasint)n,(blasint)k,
                (double)alpha,
                &(((double *)bufferA->data)[offsetA]), (blasint)ldA,
                (double)beta,
                &(((double *)bufferC->data)[offsetC]), (blasint)ldC);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function syr2k(
        int $order,
        int $uplo,
        int $trans,
        int $n,
        int $k,
        float $alpha,
        Buffer $A, int $offsetA, int $ldA,
        Buffer $B, int $offsetB, int $ldB,
        float $beta,
        Buffer $C, int $offsetC, int $ldC ) : void
 {{{ */
static PHP_METHOD(Blas, syr2k)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferA;
    php_interop_polite_math_matrix_linear_buffer_t* bufferB;
    php_interop_polite_math_matrix_linear_buffer_t* bufferC;
    zend_long order;
    zend_long uplo;
    zend_long trans;
    zend_long n;
    zend_long k;
    double alpha;
    zval* a=NULL;
    zend_long offsetA;
    zend_long ldA;
    zval* b=NULL;
    zend_long offsetB;
    zend_long ldB;
    double beta;
    zval* c=NULL;
    zend_long offsetC;
    zend_long ldC;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 16, 16)
        Z_PARAM_LONG(order)
        Z_PARAM_LONG(uplo)
        Z_PARAM_LONG(trans)
        Z_PARAM_LONG(n)
        Z_PARAM_LONG(k)
        Z_PARAM_DOUBLE(alpha)
        Z_PARAM_OBJECT(a) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetA)
        Z_PARAM_LONG(ldA)
        Z_PARAM_OBJECT(b) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetB)
        Z_PARAM_LONG(ldB)
        Z_PARAM_DOUBLE(beta)
        Z_PARAM_OBJECT(c) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetC)
        Z_PARAM_LONG(ldC)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "k", k)) {
        return;
    }
    // Check Buffer A and B
    bufferA = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_buffer_type(bufferA,"a")) {
        return;
    }
    bufferB = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(b);
    if(php_rindow_openblas_assert_buffer_type(bufferB,"b")) {
        return;
    }
    {
        zend_long rows,cols;
        if(trans==CblasNoTrans || trans==CblasConjNoTrans) {
            rows = n; cols = k;
        } else if(trans==CblasTrans || trans==CblasConjTrans) {
            rows = k; cols = n;
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "unknown transpose mode for bufferA.", 0);
            return;
        }
        if(php_rindow_openblas_assert_matrix_buffer_spec(
            "A", bufferA,rows,cols,offsetA,ldA)) {
            return;
        }
        if(php_rindow_openblas_assert_matrix_buffer_spec(
            "B", bufferB,rows,cols,offsetB,ldB)) {
            return;
        }
    }

    // Check Buffer C
    bufferC = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(c);
    if(php_rindow_openblas_assert_buffer_type(bufferC,"c")) {
        return;
    }
    if(php_rindow_openblas_assert_matrix_buffer_spec(
        "C", bufferC,n,n,offsetC,ldC)) {
        return;
    }

    // Check Buffer A and B and C
    if(bufferA->dtype!=bufferB->dtype || bufferB->dtype!=bufferC->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A and B and C", 0);
        return;
    }

    switch (bufferA->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_ssyr2k(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (blasint)n,(blasint)k,
                (float)alpha,
                &(((float *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((float *)bufferB->data)[offsetB]), (blasint)ldB,
                (float)beta,
                &(((float *)bufferC->data)[offsetC]), (blasint)ldC);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dsyr2k(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (blasint)n,(blasint)k,
                (double)alpha,
                &(((double *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((double *)bufferB->data)[offsetB]), (blasint)ldB,
                (double)beta,
                &(((double *)bufferC->data)[offsetC]), (blasint)ldC);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function trmm(
        int $order,
        int $side,
        int $uplo,
        int $trans,
        int $diag,
        int $m,
        int $n,
        float $alpha,
        Buffer $A, int $offsetA, int $ldA,
        Buffer $B, int $offsetB, int $ldB) : void
 {{{ */
static PHP_METHOD(Blas, trmm)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferA;
    php_interop_polite_math_matrix_linear_buffer_t* bufferB;
    zend_long order;
    zend_long side;
    zend_long uplo;
    zend_long trans;
    zend_long diag;
    zend_long m;
    zend_long n;
    double alpha;
    zval* a=NULL;
    zend_long offsetA;
    zend_long ldA;
    zval* b=NULL;
    zend_long offsetB;
    zend_long ldB;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 14, 14)
        Z_PARAM_LONG(order)
        Z_PARAM_LONG(side)
        Z_PARAM_LONG(uplo)
        Z_PARAM_LONG(trans)
        Z_PARAM_LONG(diag)
        Z_PARAM_LONG(m)
        Z_PARAM_LONG(n)
        Z_PARAM_DOUBLE(alpha)
        Z_PARAM_OBJECT(a) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetA)
        Z_PARAM_LONG(ldA)
        Z_PARAM_OBJECT(b) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetB)
        Z_PARAM_LONG(ldB)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "m", m)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer A
    bufferA = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_buffer_type(bufferA,"a")) {
        return;
    }
    {
        zend_long sizeA;
        if(side==CblasLeft) {
            sizeA = m;
        } else if(side==CblasRight) {
            sizeA = n;
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "unknown transpose mode for bufferA.", 0);
            return;
        }
        if(php_rindow_openblas_assert_matrix_buffer_spec(
            "A", bufferA,sizeA,sizeA,offsetA,ldA)) {
            return;
        }
    }
    bufferB = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(b);
    if(php_rindow_openblas_assert_buffer_type(bufferB,"b")) {
        return;
    }
    if(php_rindow_openblas_assert_matrix_buffer_spec(
        "B", bufferB,m,n,offsetB,ldB)) {
        return;
    }

    // Check Buffer A and B
    if(bufferA->dtype!=bufferB->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A and B", 0);
        return;
    }

    switch (bufferA->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_strmm(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_SIDE)side,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (OPENBLAS_CONST enum CBLAS_DIAG)diag,
                (blasint)m,(blasint)n,
                (float)alpha,
                &(((float *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((float *)bufferB->data)[offsetB]), (blasint)ldB);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dtrmm(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_SIDE)side,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (OPENBLAS_CONST enum CBLAS_DIAG)diag,
                (blasint)m,(blasint)n,
                (double)alpha,
                &(((double *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((double *)bufferB->data)[offsetB]), (blasint)ldB);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function trsm(
        int $order,
        int $side,
        int $uplo,
        int $trans,
        int $diag,
        int $m,
        int $n,
        float $alpha,
        Buffer $A, int $offsetA, int $ldA,
        Buffer $B, int $offsetB, int $ldB) : void
 {{{ */
static PHP_METHOD(Blas, trsm)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferA;
    php_interop_polite_math_matrix_linear_buffer_t* bufferB;
    zend_long order;
    zend_long side;
    zend_long uplo;
    zend_long trans;
    zend_long diag;
    zend_long m;
    zend_long n;
    double alpha;
    zval* a=NULL;
    zend_long offsetA;
    zend_long ldA;
    zval* b=NULL;
    zend_long offsetB;
    zend_long ldB;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 14, 14)
        Z_PARAM_LONG(order)
        Z_PARAM_LONG(side)
        Z_PARAM_LONG(uplo)
        Z_PARAM_LONG(trans)
        Z_PARAM_LONG(diag)
        Z_PARAM_LONG(m)
        Z_PARAM_LONG(n)
        Z_PARAM_DOUBLE(alpha)
        Z_PARAM_OBJECT(a) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetA)
        Z_PARAM_LONG(ldA)
        Z_PARAM_OBJECT(b) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetB)
        Z_PARAM_LONG(ldB)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "m", m)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer A
    bufferA = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_buffer_type(bufferA,"a")) {
        return;
    }
    {
        zend_long sizeA;
        if(side==CblasLeft) {
            sizeA = m;
        } else if(side==CblasRight) {
            sizeA = n;
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "unknown transpose mode for bufferA.", 0);
            return;
        }
        if(php_rindow_openblas_assert_matrix_buffer_spec(
            "A", bufferA,sizeA,sizeA,offsetA,ldA)) {
            return;
        }
    }
    bufferB = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(b);
    if(php_rindow_openblas_assert_buffer_type(bufferB,"b")) {
        return;
    }
    if(php_rindow_openblas_assert_matrix_buffer_spec(
        "B", bufferB,m,n,offsetB,ldB)) {
        return;
    }

    // Check Buffer A and B
    if(bufferA->dtype!=bufferB->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A and B", 0);
        return;
    }

    switch (bufferA->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_strsm(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_SIDE)side,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (OPENBLAS_CONST enum CBLAS_DIAG)diag,
                (blasint)m,(blasint)n,
                (float)alpha,
                &(((float *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((float *)bufferB->data)[offsetB]), (blasint)ldB);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_dtrsm(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_SIDE)side,
                (OPENBLAS_CONST enum CBLAS_UPLO)uplo,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (OPENBLAS_CONST enum CBLAS_DIAG)diag,
                (blasint)m,(blasint)n,
                (double)alpha,
                &(((double *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((double *)bufferB->data)[offsetB]), (blasint)ldB);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

/* Method Rindow\OpenBLAS\Blas::
    public function omatcopy(
        int $order,
        int $trans,
        int $m,
        int $n,
        float $alpha,
        BufferInterface $A, int $offsetA, int $ldA,
        BufferInterface $B, int $offsetB, int $ldB,
    ) : void
 {{{ */
static PHP_METHOD(Blas, omatcopy)
{
    php_interop_polite_math_matrix_linear_buffer_t* bufferA;
    php_interop_polite_math_matrix_linear_buffer_t* bufferB;
    zend_long order;
    zend_long trans;
    zend_long m;
    zend_long n;
    double alpha;
    zval* a=NULL;
    zend_long offsetA;
    zend_long ldA;
    zval* b=NULL;
    zend_long offsetB;
    zend_long ldB;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 11, 11)
        Z_PARAM_LONG(order)
        Z_PARAM_LONG(trans)
        Z_PARAM_LONG(m)
        Z_PARAM_LONG(n)
        Z_PARAM_DOUBLE(alpha)

        Z_PARAM_OBJECT(a) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetA)
        Z_PARAM_LONG(ldA)
        Z_PARAM_OBJECT(b) // Interop\Polite\Math\Matrix\LinearBuffer
        Z_PARAM_LONG(offsetB)

        Z_PARAM_LONG(ldB)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        "m", m)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        "n", n)) {
        return;
    }
    // Check Buffer A
    bufferA = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_buffer_type(bufferA,"a")) {
        return;
    }
    if(php_rindow_openblas_assert_matrix_buffer_spec("A", bufferA,m,n,offsetA,ldA)) {
        return;
    }
    bufferB = Z_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_OBJ_P(b);
    if(php_rindow_openblas_assert_buffer_type(bufferB,"b")) {
        return;
    }
    {
        zend_long rows,cols;
        if(trans==CblasNoTrans || trans==CblasConjNoTrans) {
            rows = m; cols = n;
        } else if(trans==CblasTrans || trans==CblasConjTrans) {
            rows = n; cols = m;
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "unknown transpose mode for bufferA.", 0);
            return;
        }
        if(php_rindow_openblas_assert_matrix_buffer_spec("B", bufferB,rows,cols,offsetB,ldB)) {
            return;
        }
    }

    // Check Buffer A and B
    if(bufferA->dtype!=bufferB->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A and B", 0);
        return;
    }

    switch (bufferA->dtype) {
        case php_interop_polite_math_matrix_dtype_float32:
            cblas_somatcopy(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (blasint)m,(blasint)n,
                (float)alpha,
                &(((float *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((float *)bufferB->data)[offsetB]), (blasint)ldB);
            break;
        case php_interop_polite_math_matrix_dtype_float64:
            cblas_domatcopy(
                (OPENBLAS_CONST enum CBLAS_ORDER)order,
                (OPENBLAS_CONST enum CBLAS_TRANSPOSE)trans,
                (blasint)m,(blasint)n,
                (double)alpha,
                &(((double *)bufferA->data)[offsetA]), (blasint)ldA,
                &(((double *)bufferB->data)[offsetB]), (blasint)ldB);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_scal, 0, 0, 5)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_axpy, 0, 0, 8)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
    ZEND_ARG_OBJ_INFO(0, y, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, incY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_dot, 0, 0, 7)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
    ZEND_ARG_OBJ_INFO(0, y, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, incY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_asum, 0, 0, 4)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_iamax, 0, 0, 4)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
ZEND_END_ARG_INFO()

#ifdef OPENBLAS_HAVE_IAMIN
ZEND_BEGIN_ARG_INFO_EX(ai_Blas_iamin, 0, 0, 4)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_copy, 0, 0, 7)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
    ZEND_ARG_OBJ_INFO(0, y, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, incY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_nrm2, 0, 0, 4)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_rotg, 0, 0, 8)
    ZEND_ARG_OBJ_INFO(0, a, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetA)
    ZEND_ARG_OBJ_INFO(0, b, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetB)
    ZEND_ARG_OBJ_INFO(0, c, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetC)
    ZEND_ARG_OBJ_INFO(0, s, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetS)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_rot, 0, 0, 11)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
    ZEND_ARG_OBJ_INFO(0, y, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, incY)
    ZEND_ARG_OBJ_INFO(0, c, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetC)
    ZEND_ARG_OBJ_INFO(0, s, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetS)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_rotmg, 0, 0, 10)
    ZEND_ARG_OBJ_INFO(0, d1, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetD1)
    ZEND_ARG_OBJ_INFO(0, d2, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetD2)
    ZEND_ARG_OBJ_INFO(0, b1, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetB1)
    ZEND_ARG_OBJ_INFO(0, b2, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetB2)
    ZEND_ARG_OBJ_INFO(0, p, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetP)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_rotm, 0, 0, 9)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
    ZEND_ARG_OBJ_INFO(0, y, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, incY)
    ZEND_ARG_OBJ_INFO(0, p, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetP)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_swap, 0, 0, 7)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
    ZEND_ARG_OBJ_INFO(0, y, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, incY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_gemv, 0, 0, 15)
    ZEND_ARG_INFO(0, order)
    ZEND_ARG_INFO(0, trans)
    ZEND_ARG_INFO(0, m)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, a, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetA)
    ZEND_ARG_INFO(0, ldA)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetX)
    ZEND_ARG_INFO(0, incX)
    ZEND_ARG_INFO(0, beta)
    ZEND_ARG_OBJ_INFO(0, x, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetY)
    ZEND_ARG_INFO(0, incY)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_gemm, 0, 0, 17)
    ZEND_ARG_INFO(0, order)
    ZEND_ARG_INFO(0, transA)
    ZEND_ARG_INFO(0, transB)
    ZEND_ARG_INFO(0, m)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, k)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, a, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetA)
    ZEND_ARG_INFO(0, ldA)
    ZEND_ARG_OBJ_INFO(0, b, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetB)
    ZEND_ARG_INFO(0, ldB)
    ZEND_ARG_INFO(0, beta)
    ZEND_ARG_OBJ_INFO(0, c, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetC)
    ZEND_ARG_INFO(0, ldC)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_symm, 0, 0, 16)
    ZEND_ARG_INFO(0, order)
    ZEND_ARG_INFO(0, side)
    ZEND_ARG_INFO(0, uplo)
    ZEND_ARG_INFO(0, m)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, a, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetA)
    ZEND_ARG_INFO(0, ldA)
    ZEND_ARG_OBJ_INFO(0, b, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetB)
    ZEND_ARG_INFO(0, ldB)
    ZEND_ARG_INFO(0, beta)
    ZEND_ARG_OBJ_INFO(0, c, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetC)
    ZEND_ARG_INFO(0, ldC)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_syrk, 0, 0, 13)
    ZEND_ARG_INFO(0, order)
    ZEND_ARG_INFO(0, uplo)
    ZEND_ARG_INFO(0, trans)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, k)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, a, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetA)
    ZEND_ARG_INFO(0, ldA)
    ZEND_ARG_INFO(0, beta)
    ZEND_ARG_OBJ_INFO(0, c, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetC)
    ZEND_ARG_INFO(0, ldC)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_syr2k, 0, 0, 16)
    ZEND_ARG_INFO(0, order)
    ZEND_ARG_INFO(0, uplo)
    ZEND_ARG_INFO(0, trans)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, k)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, a, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetA)
    ZEND_ARG_INFO(0, ldA)
    ZEND_ARG_OBJ_INFO(0, b, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetB)
    ZEND_ARG_INFO(0, ldB)
    ZEND_ARG_INFO(0, beta)
    ZEND_ARG_OBJ_INFO(0, c, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetC)
    ZEND_ARG_INFO(0, ldC)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_trmm, 0, 0, 14)
    ZEND_ARG_INFO(0, order)
    ZEND_ARG_INFO(0, side)
    ZEND_ARG_INFO(0, uplo)
    ZEND_ARG_INFO(0, trans)
    ZEND_ARG_INFO(0, diag)
    ZEND_ARG_INFO(0, m)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, a, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetA)
    ZEND_ARG_INFO(0, ldA)
    ZEND_ARG_OBJ_INFO(0, b, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetB)
    ZEND_ARG_INFO(0, ldB)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_trsm, 0, 0, 14)
    ZEND_ARG_INFO(0, order)
    ZEND_ARG_INFO(0, side)
    ZEND_ARG_INFO(0, uplo)
    ZEND_ARG_INFO(0, trans)
    ZEND_ARG_INFO(0, diag)
    ZEND_ARG_INFO(0, m)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, a, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetA)
    ZEND_ARG_INFO(0, ldA)
    ZEND_ARG_OBJ_INFO(0, b, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetB)
    ZEND_ARG_INFO(0, ldB)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_omatcopy, 0, 0, 11)
    ZEND_ARG_INFO(0, order)
    ZEND_ARG_INFO(0, trans)
    ZEND_ARG_INFO(0, m)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(0, alpha)
    ZEND_ARG_OBJ_INFO(0, a, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetA)
    ZEND_ARG_INFO(0, ldA)
    ZEND_ARG_OBJ_INFO(0, b, Interop\\Polite\\Math\\Matrix\\LinearBuffer, 0)
    ZEND_ARG_INFO(0, offsetB)
    ZEND_ARG_INFO(0, ldB)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Blas_void, 0, 0, 0)
ZEND_END_ARG_INFO()

/* {{{ Rindow\OpenBLAS\Blas function entries */
static zend_function_entry php_rindow_openblas_blas_me[] = {
    /* clang-format off */
    PHP_ME(Blas, getNumThreads, ai_Blas_void, ZEND_ACC_PUBLIC)
    PHP_ME(Blas, getNumProcs,   ai_Blas_void, ZEND_ACC_PUBLIC)
    PHP_ME(Blas, getConfig,     ai_Blas_void, ZEND_ACC_PUBLIC)
    PHP_ME(Blas, getCorename,   ai_Blas_void, ZEND_ACC_PUBLIC)
    PHP_ME(Blas, getParallel,   ai_Blas_void, ZEND_ACC_PUBLIC)
    PHP_ME(Blas, scal,  ai_Blas_scal,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, axpy,  ai_Blas_axpy,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, dot,   ai_Blas_dot,   ZEND_ACC_PUBLIC)
    PHP_ME(Blas, asum,  ai_Blas_asum,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, iamax, ai_Blas_iamax, ZEND_ACC_PUBLIC)
#ifdef OPENBLAS_HAVE_IAMIN
    PHP_ME(Blas, iamin, ai_Blas_iamin, ZEND_ACC_PUBLIC)
#endif
    PHP_ME(Blas, copy,  ai_Blas_copy,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, nrm2,  ai_Blas_nrm2,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, rotg,  ai_Blas_rotg,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, rot,   ai_Blas_rot,   ZEND_ACC_PUBLIC)
    PHP_ME(Blas, rotmg, ai_Blas_rotmg, ZEND_ACC_PUBLIC)
    PHP_ME(Blas, rotm,  ai_Blas_rotm,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, swap,  ai_Blas_swap,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, gemv,  ai_Blas_gemv,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, gemm,  ai_Blas_gemm,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, symm,  ai_Blas_symm,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, syrk,  ai_Blas_syrk,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, syr2k, ai_Blas_syr2k, ZEND_ACC_PUBLIC)
    PHP_ME(Blas, trmm,  ai_Blas_trmm,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, trsm,  ai_Blas_trsm,  ZEND_ACC_PUBLIC)
    PHP_ME(Blas, omatcopy, ai_Blas_omatcopy, ZEND_ACC_PUBLIC)
    PHP_FE_END
    /* clang-format on */
};
/* }}} */

/* Class Rindow\OpenBLAS\Blas {{{ */
static zend_class_entry* rindow_openblas_blas_ce;

void php_rindow_openblas_blas_init_ce(INIT_FUNC_ARGS)
{
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, "Rindow\\OpenBLAS", "Blas", php_rindow_openblas_blas_me);
    rindow_openblas_blas_ce = zend_register_internal_class(&ce);
    rindow_openblas_blas_ce->create_object = php_rindow_openblas_blas_create_object;

    memcpy(&rindow_openblas_blas_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    rindow_openblas_blas_object_handlers.offset    = 0;
    rindow_openblas_blas_object_handlers.free_obj  = php_rindow_openblas_blas_free_object;
    rindow_openblas_blas_object_handlers.clone_obj = NULL;

    //zend_class_implements(rindow_openblas_blas_ce, 2, spl_ce_ArrayAccess, spl_ce_Countable);
}
/* }}} */
