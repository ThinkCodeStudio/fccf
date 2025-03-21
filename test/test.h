#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>
#include <stdint.h>

#define TEST(code)  \
if(code){           \
    printf("[ok] %s\n", #code);\
}else{\
    printf("[no] %s\n", #code);\
}

#endif