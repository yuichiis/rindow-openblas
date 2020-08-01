/*
   X(i) := rand(seed)

   Method Rindow\OpenBLAS\Math::
    public function randomUniformFloat(
        int $n,
        Buffer $X, int $offsetX, int $incX,
        float $low,
        float $high,
        int $seed
        ) : void
 {{{ */
#include <ext/standard/php_rand.h>

static PHP_METHOD(Math, randomUniform)
{
    php_rindow_openblas_buffer_t* bufferX;
    zend_long n;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    zval* low_val=NULL;
    zval* high_val=NULL;
    zend_long low_int;
    zend_long high_int;
    double low_float;
    double high_float;
    zend_long seed;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 7, 7)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT_OF_CLASS(x,php_rindow_openblas_buffer_ce)
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
        Z_PARAM_ZVAL(low_val)
        Z_PARAM_ZVAL(high_val)
        Z_PARAM_LONG(seed)
    ZEND_PARSE_PARAMETERS_END();

    // Check Buffer X
    bufferX = Z_RINDOW_OPENBLAS_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_vector_buffer_spec(
        PHP_RINDOW_OPENBLAS_ASSERT_X, bufferX,n,offsetX,incX)) {
        return;
    }

    if(php_rindow_openblas_dtype_is_float(bufferX->dtype)) {
        if(php_rindow_openblas_val2float(low_val,&low_float,"low must be float or int")) {
            return;
        }
        if(php_rindow_openblas_val2float(high_val,&high_float,"high must be float or int")) {
            return;
        }
    } else if(php_rindow_openblas_dtype_is_int(bufferX->dtype)) {
        if(php_rindow_openblas_val2int(low_val,&low_int,"low must be float or int")) {
            return;
        }
        if(php_rindow_openblas_val2int(high_val,&high_int,"high must be float or int")) {
            return;
        }
    } else {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unsupported data type.", 0);
        return;
    }
    
    php_mt_srand(seed);

    switch(bufferX->dtype) {
        case php_rindow_openblas_dtype_float32:
            {
                float *x = &(((float *)bufferX->data)[offsetX]);
                zend_long i;
                for(i=0; i<n; i++,x+=incX) {
                    //*x = (float)PHP_MT_RAND_MAX;
                    
                    *x =/* (float)low_float+*/(float)php_mt_rand()/(float)PHP_MT_RAND_MAX*((float)high_float-(float)low_float);
                    
                }
            }
            break;
        case php_rindow_openblas_dtype_float64:
            {
                double *x = &(((double *)bufferX->data)[offsetX]);
                zend_long i;
                for(i=0; i<n; i++,x+=incX) {
                    *x = (double)low_float+(double)php_mt_rand()*((double)high_float-(double)low_float+1.0)/(1.0+(double)PHP_MT_RAND_MAX);
                }
            }
            break;
        default:
            {
                zend_long i;
                for(i=0; i<n; i++) {
                    zend_long value;
                    value = php_mt_rand_range(low_int,high_int);
                    rindow_openblas_math_set_integer(
                        bufferX->dtype, bufferX->data, offsetX,incX,
                        i, value);
                }
            }
            break;
    }
}


/* }}} */
