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
#endif
#ifdef __clang__
    printf("__clang__=%d\n",__clang__);
#endif

}