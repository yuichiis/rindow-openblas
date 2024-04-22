#include <stdio.h>

void main()
{
#ifdef _MSC_VER
    printf("_MSC_VER=%d\n",_MSC_VER);
#if (_MSC_VER % 100 ) <= 16
    printf("VC2017\n");
#else
    printf("VC2019\n");
#endif
#endif
#ifdef __GNUC__
    printf("__GNUC__=%d\n",__GNUC__);
    printf("__GNUC_MINOR__=%d\n",__GNUC_MINOR__);
    printf("__GNUC_PATCHLEVEL__=%d\n",__GNUC_PATCHLEVEL__);
#endif
#ifdef __clang__
    printf("__clang__=%d\n",__clang__);
    printf("__clang_major__=%d\n",__clang_major__);
    printf("__clang_build_version__=%d\n",__clang_build_version__);
#endif

}