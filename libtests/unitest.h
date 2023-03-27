#ifndef UNITTEST_H_
#define UNITTEST_H_ 1
#include <stdio.h>

#define TEST(t) { \
    char *msg; \
    msg=t##(); \
    if(msg==NULL) { \
        printf("%s: success\n",#t); \
    } else { \
        printf("%s: %s\n",#t,msg); \
    } \
}

static char TestExceptionMessage[1024];
#define ASSERT_EQUAL(type,r,v) { \
    if(r!=v) { \
        sprintf_s(TestExceptionMessage,sizeof(TestExceptionMessage),"exception not equal(%"#type",%"#type"): %s(%d)",r,v,__FILE__, __LINE__); \
        return TestExceptionMessage; \
    } \
}

#endif
