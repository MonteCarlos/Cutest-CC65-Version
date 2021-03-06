#include "CuTest_internal.h"

bool CuAssertArrayElementsConstant_LineMsg (CuTest_t *tc, const char *file, unsigned long int line, const char *message,
        const void *expected, const void *actual, CuSize_t elementsize, CuSize_t len) {
    if (tc) {
        (void)message; //Work around unused param

        CuSize_t i = 0, j = 0;
        CuSize_t arrayIndex = 0;

        ++tc->assertCnt;

        if (0 == elementsize) {
            CuFail_Line (tc, file, line, "0==elementsize", NULL);
            return true;
        }

        if (0 == len) {
            CuFail_Line (tc, file, line, "0==len", NULL);
            return true;
        }

        for (j = 0; j < len; ++j) {
            for (i = 0; i < elementsize; ++i) {
                if ( ( (uint8_t *) expected) [i] != ( (uint8_t *) actual) [arrayIndex] ) {
                    CuFail_Line (tc, file, line, "Array element differs from given constant at ", NULL);
                    CuTestAppendMessage (tc, "%d.", j);
                    return true;
                }

                arrayIndex += 1;
            }
        }

        return false;
    }

    CuFail_Line (tc, file, line, "Testcase invalid", NULL);
    return true;
}


