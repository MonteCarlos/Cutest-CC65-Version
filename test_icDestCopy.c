#include <stdheaders.h>
#include "mem.h"

void testCopy(void){
    char string[] = "count:0";
    static uint8_t i = 0;

    callIncrementalDestCopy_zpPtrs(sizeof(string)-1, string, (void*)0x400);
    for (i = 0; i< 8; ++i){
        string[sizeof(string)-2] = i;
        incrementalDestCopy_zpPtrs(sizeof(string)-1);
    }
}

void main(void){
    testCopy();
}

