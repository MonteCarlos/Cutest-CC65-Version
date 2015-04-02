
#include "CuTest_internal.h"

bool CuAssertArrayEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
	const void* expected, const void* actual, size_t elementsize, size_t len)
{
    size_t i=0,j=0;
    size_t arrayIndex = 0;

    if (0 == elementsize) {
        CuFail_Line(tc, file, line, "0==elementsize", NULL);
        return true;
    }
    if (0 == len) {
        CuFail_Line(tc, file, line, "0==len", NULL);
        return true;
    }

    for (j = 0; j < len; ++j){
        for (i = 0; i < elementsize; ++i){
            if ( ((uint8_t*)expected)[arrayIndex] != ((uint8_t*)actual)[arrayIndex] ){
                CuFail_Line(tc, file, line, "Arrays not equal at pos ", NULL);
                CuTestAppendMessage(tc, "%d/%d (%d/%d).", j,i,((uint8_t*)expected)[arrayIndex],((uint8_t*)actual)[arrayIndex]);
                return true;
            }
            arrayIndex += 1;
        }
    }

	return false;
}

