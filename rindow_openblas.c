/* rindow_openblas extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <php.h>
#include <Zend/zend_interfaces.h>
#include <Zend/zend_exceptions.h>
#include <ext/spl/spl_iterators.h>
#include <ext/spl/spl_exceptions.h>
#include "ext/standard/info.h"
#include <Interop/Polite/Math/Matrix.h>
#include "php_rindow_openblas.h"

#if _MSC_VER
extern int rindow_load_openblas_dll();
extern void rindow_unload_openblas_dll();
#endif

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
    ZEND_PARSE_PARAMETERS_START(0, 0) \
    ZEND_PARSE_PARAMETERS_END()
#endif

int php_rindow_openblas_common_dtype_to_valuesize(zend_long dtype)
{
    switch (dtype) {
        case php_interop_polite_math_matrix_dtype_bool:
        case php_interop_polite_math_matrix_dtype_int8:
        case php_interop_polite_math_matrix_dtype_uint8:
        case php_interop_polite_math_matrix_dtype_float8:
            return 1;
        case php_interop_polite_math_matrix_dtype_int16:
        case php_interop_polite_math_matrix_dtype_uint16:
        case php_interop_polite_math_matrix_dtype_float16:
            return 2;
        case php_interop_polite_math_matrix_dtype_int32:
        case php_interop_polite_math_matrix_dtype_uint32:
        case php_interop_polite_math_matrix_dtype_float32:
            return 4;
        case php_interop_polite_math_matrix_dtype_int64:
        case php_interop_polite_math_matrix_dtype_uint64:
        case php_interop_polite_math_matrix_dtype_float64:
            return 8;
    }
    return 0;
}


int php_rindow_openblas_common_dtype_is_int(zend_long dtype)
{
    switch (dtype) {
        case php_interop_polite_math_matrix_dtype_int8:
        case php_interop_polite_math_matrix_dtype_uint8:
        case php_interop_polite_math_matrix_dtype_int16:
        case php_interop_polite_math_matrix_dtype_uint16:
        case php_interop_polite_math_matrix_dtype_int32:
        case php_interop_polite_math_matrix_dtype_uint32:
        case php_interop_polite_math_matrix_dtype_int64:
        case php_interop_polite_math_matrix_dtype_uint64:
            return 1;
    }
    return 0;
}

int php_rindow_openblas_common_dtype_is_float(zend_long dtype)
{
    switch (dtype) {
        case php_interop_polite_math_matrix_dtype_float8:
        case php_interop_polite_math_matrix_dtype_float16:
        case php_interop_polite_math_matrix_dtype_float32:
        case php_interop_polite_math_matrix_dtype_float64:
            return 1;
    }
    return 0;
}

int php_rindow_openblas_common_dtype_is_bool(zend_long dtype)
{
    switch (dtype) {
        case php_interop_polite_math_matrix_dtype_bool:
            return 1;
    }
    return 0;
}

int php_rindow_openblas_assert_shape_parameter(
    char* name, zend_long n)
{
    if(n<1) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Argument %s must be greater than 0.",name);
        return -1;
    }
    return 0;
}

int php_rindow_openblas_assert_vector_buffer_spec(
    char* name,php_interop_polite_math_matrix_linear_buffer_t *buffer,
    zend_long n, zend_long offset, zend_long inc)
{
    if(buffer->data==NULL) {
        zend_throw_exception_ex(spl_ce_DomainException, 0, "buffer%s is not initialized",name);
        return -1;
    }
    if(offset<0) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Argument offset%s must be greater than or equals 0.",name);
        return -1;
    }
    if(inc<1) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Argument inc%s must be greater than 0.",name);
        return -1;
    }
    if(offset+(n-1)*inc >= buffer->size) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Vector specification too large for buffer%s.",name);
        return -1;
    }

    return 0;
}

int php_rindow_openblas_assert_matrix_buffer_spec(
    char* name, php_interop_polite_math_matrix_linear_buffer_t *buffer,
    zend_long m,zend_long n, zend_long offset, zend_long ld)
{
    if(buffer->data==NULL) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "uninitialized array: %s",name);
        return -1;
    }
    if(offset<0) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Argument offset%s must be greater than or equals 0.",name);
        return -1;
    }
    if(ld<1) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Argument ld%s must be greater than 0.",name);
        return -1;
    }
    if(offset+(m-1)*ld+(n-1) >= buffer->size) {
        zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Matrix specification too large for buffer%s.",name);
        return -1;
    }

    return 0;
}

int php_rindow_openblas_assert_buffer_size(
    php_interop_polite_math_matrix_linear_buffer_t *buffer,
    zend_long offset,zend_long size,
    char* message)
{
    if(size<1 || offset<0 ||
        buffer->size < offset+size) {
        zend_throw_exception(spl_ce_InvalidArgumentException, message, 0);
        return -1;
    }
    return 0;
}

int php_rindow_openblas_assert_buffer_type(
    php_interop_polite_math_matrix_linear_buffer_t *buffer,
    char* name)
{
    if(!php_interop_polite_math_matrix_is_linear_buffer(buffer)) {
        zend_throw_exception_ex(zend_ce_type_error, 0, "%s must implement interface %s",
            name,PHP_INTEROP_POLITE_MATH_MATRIX_LINEAR_BUFFER_CLASSNAME);
        return 1;
    }
    return 0;
}

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(rindow_openblas)
{
#if defined(ZTS) && defined(COMPILE_DL_RINDOW_OPENBLAS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(rindow_openblas)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "rindow_openblas support", "enabled");
    php_info_print_table_end();
}
/* }}} */

/* {{{ rindow_openblas_functions[]
 */
//static const zend_function_entry rindow_openblas_functions[] = {
//};
/* }}} */

PHP_MINIT_FUNCTION(rindow_openblas)
{
#if _MSC_VER
    int rc=rindow_load_openblas_dll();
    if(rc!=0) {
        rindow_unload_openblas_dll();
        return FAILURE;
    }
#endif
    php_rindow_openblas_buffer_init_ce(INIT_FUNC_ARGS_PASSTHRU);
    php_rindow_openblas_blas_init_ce(INIT_FUNC_ARGS_PASSTHRU);
    php_rindow_openblas_lapack_init_ce(INIT_FUNC_ARGS_PASSTHRU);
    php_rindow_openblas_math_init_ce(INIT_FUNC_ARGS_PASSTHRU);
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(rindow_openblas)
{
#if _MSC_VER
    rindow_unload_openblas_dll();
#endif
    return SUCCESS;
}

/* {{{ php_rindow_openblas_module_entry
 */
zend_module_entry rindow_openblas_module_entry = {
    STANDARD_MODULE_HEADER,
    "rindow_openblas",					/* Extension name */
    NULL,			                    /* zend_function_entry */
    PHP_MINIT(rindow_openblas),			/* PHP_MINIT - Module initialization */
    PHP_MSHUTDOWN(rindow_openblas),     /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(rindow_openblas),			/* PHP_RINIT - Request initialization */
    NULL,							    /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(rindow_openblas),			/* PHP_MINFO - Module info */
    PHP_RINDOW_OPENBLAS_VERSION,		/* Version */
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_RINDOW_OPENBLAS
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(rindow_openblas)
#endif
