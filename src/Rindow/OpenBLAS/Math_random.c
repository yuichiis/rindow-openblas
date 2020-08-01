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
                php_mt_rand_range(low_int,high_int);
                float *x = &(((float *)bufferX->data)[offsetX]);
                zend_long i;
                for(i=0; i<n; i++,x+=incX) {
                    *x = ((float)high_float-(float)low_float)*(float)php_mt_rand()/(float)PHP_MT_RAND_MAX+(float)low_float;
                }
            }
            break;
        case php_rindow_openblas_dtype_float64:
            {
                double *x = &(((double *)bufferX->data)[offsetX]);
                zend_long i;
                for(i=0; i<n; i++,x+=incX) {
                    *x = (high_float-low_float)*(double)php_mt_rand()/(double)PHP_MT_RAND_MAX+low_float;
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

/*
   A(X[i]) := Y(i)

   Method Rindow\OpenBLAS\Math::
    public function scatterArxis1(
        int $m,
        int $n,
        Buffer $A, int $offsetA, int $ldA,
        Buffer $X, int $offsetX, int $incX,
        Buffer $Y, int $offsetY, int $incY ) : void
 {{{ */
static PHP_METHOD(Math, scatterAxis1)
{
    php_rindow_openblas_buffer_t* bufferA;
    php_rindow_openblas_buffer_t* bufferX;
    php_rindow_openblas_buffer_t* bufferY;
    zend_long m;
    zend_long n;
    zval* a=NULL;
    zend_long offsetA;
    zend_long ldA;
    zval* x=NULL;
    zend_long offsetX;
    zend_long incX;
    zval* y=NULL;
    zend_long offsetY;
    zend_long incY;

    //if (zend_parse_parameters(ZEND_NUM_ARGS(), "llOllOllOll",
    //        &m,
    //        &n,
    //        &a,php_rindow_openblas_buffer_ce,&offsetA,&ldA,
    //        &x,php_rindow_openblas_buffer_ce,&offsetX,&incX,
    //        &y,php_rindow_openblas_buffer_ce,&offsetY,&incY) == FAILURE) {
    //    zend_throw_exception(spl_ce_InvalidArgumentException, "Invalid Arguments", 0);
    //    return;
    //}
    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 11, 11)
        Z_PARAM_LONG(m)
        Z_PARAM_LONG(n)
        Z_PARAM_OBJECT_OF_CLASS(a,php_rindow_openblas_buffer_ce)
        Z_PARAM_LONG(offsetA)
        Z_PARAM_LONG(ldA)
        Z_PARAM_OBJECT_OF_CLASS(x,php_rindow_openblas_buffer_ce)
        Z_PARAM_LONG(offsetX)
        Z_PARAM_LONG(incX)
        Z_PARAM_OBJECT_OF_CLASS(y,php_rindow_openblas_buffer_ce)
        Z_PARAM_LONG(offsetY)
        Z_PARAM_LONG(incY)
    ZEND_PARSE_PARAMETERS_END();

    if(php_rindow_openblas_assert_shape_parameter(
        PHP_RINDOW_OPENBLAS_ASSERT_M, m)) {
        return;
    }
    if(php_rindow_openblas_assert_shape_parameter(
        PHP_RINDOW_OPENBLAS_ASSERT_N, n)) {
        return;
    }
    // Check Buffer A
    bufferA = Z_RINDOW_OPENBLAS_BUFFER_OBJ_P(a);
    if(php_rindow_openblas_assert_matrix_buffer_spec(
        PHP_RINDOW_OPENBLAS_ASSERT_A, bufferA,m,n,offsetA,ldA)) {
        return;
    }

    // Check Buffer X
    bufferX = Z_RINDOW_OPENBLAS_BUFFER_OBJ_P(x);
    if(php_rindow_openblas_assert_vector_buffer_spec(
        PHP_RINDOW_OPENBLAS_ASSERT_X, bufferX,m,offsetX,incX)) {
        return;
    }

    // Check Buffer Y
    bufferY = Z_RINDOW_OPENBLAS_BUFFER_OBJ_P(y);
    if(php_rindow_openblas_assert_vector_buffer_spec(
        PHP_RINDOW_OPENBLAS_ASSERT_Y, bufferY,m,offsetY,incY)) {
        return;
    }

    // Check Buffer A and Y
    if(bufferA->dtype!=bufferY->dtype) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Unmatch data type for A and Y", 0);
        return;
    }
    if(bufferX->dtype==php_rindow_openblas_dtype_bool) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Data type of BufferX must not be bool", 0);
        return;
    }

    switch (bufferA->dtype) {
        case php_rindow_openblas_dtype_float32:
            {
                float *a = &(((float *)bufferA->data)[offsetA]);
                float *y = &(((float *)bufferY->data)[offsetY]);
                zend_long i,selector;
                for(i=0; i<m; i++) {
                    if(rindow_openblas_math_get_integer(
                                bufferX->dtype, bufferX->data, offsetX,incX,
                                i, &selector)) {
                        zend_throw_exception(spl_ce_RuntimeException, "Unsupported data type of label number.", 0);
                        return;
                    }
                    if(selector<0||selector>=n) {
                        zend_throw_exception(spl_ce_RuntimeException, "Label number is out of bounds.", 0);
                        return;
                    }
                    a[i*ldA+selector] = y[i*incY];
                }
            }
            break;
        case php_rindow_openblas_dtype_float64:
            {
                double *a = &(((double *)bufferA->data)[offsetA]);
                double *y = &(((double *)bufferY->data)[offsetX]);
                zend_long i,selector;
                for(i=0; i<m; i++) {
                    if(rindow_openblas_math_get_integer(
                                bufferX->dtype, bufferX->data, offsetX,incX,
                                i, &selector)) {
                        zend_throw_exception(spl_ce_RuntimeException, "Unsupported data type of label number.", 0);
                        return;
                    }
                    if(selector<0||selector>=n) {
                        zend_throw_exception(spl_ce_RuntimeException, "Label number is out of bounds.", 0);
                        return;
                    }
                    a[i*ldA+selector] = y[i*incY];
                }
            }
            break;
        default:
            zend_throw_exception(spl_ce_RuntimeException, "Unsupported data type.", 0);
            return;
    }
}
/* }}} */
