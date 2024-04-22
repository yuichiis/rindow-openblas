/*
// it will patch to next matlib

int32_t rindow_matlib_common_rand()
{
#ifdef _MSC_VER
#if (_MSC_VER % 100 ) <= 16
    // VS2017
    int32_t number;
    number = (((((int32_t)rand())<<17)|(((int32_t)rand())<<2)) ^ (int32_t)rand());
    return (int32_t)(number & 0x7fffffff);
#else
    // VS2019
    unsigned int number;
    if(rand_s( &number )) {
        return 0;
    }
    return (int32_t)(number & 0x7fffffff);
#endif
#else
    // Linux
    return random();
#endif
}
void rindow_matlib_common_srand(int32_t seed)
{
#ifdef _MSC_VER
#if (_MSC_VER % 100 ) <= 16
    // VS2017
    srand((unsigned int)seed);
#endif
#else
    // Linux
    srandom(seed);
#endif
}
*/