#include "CuTest_internal.h"

bool CuAssertArrayEqualsStepFunc_LineMsg(CuTest_t* tc, const char* file, unsigned long int line, const char* message,
	bool (*stepfunc)(size_t index, void* expected), const void* actual, CuSize_t elementsize, CuSize_t len)
{
    if (tc){
        (void)message; //Work around unused param

        CuSize_t i=0,j=0;
        CuSize_t arrayIndex = 0;
        void *expected = CuAlloc (elementsize);
        bool error = false;
        uint8_t expectedelement, actualelement;

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
            if ( stepfunc (j, expected) ) {
                CuFail_Line (tc, file, line, "Callback failed at pos ", NULL);
                CuTestAppendMessage (tc, "%d.", j);

                error = true;
                break;
            }

            for (i = 0; i < elementsize; ++i) {
                expectedelement = ( (uint8_t *) expected) [i];
                actualelement = ( (uint8_t *) actual) [arrayIndex];

                if (  expectedelement != actualelement ) {
                    CuFail_Line (tc, file, line, "Arrays not equal at pos ", NULL);
                    CuTestAppendMessage (tc, "%u(%u).", j, i);
                    CuStringAppendISvsNOT (tc->message, "%d", (int) expectedelement, (int) actualelement);
                    error = true;
                    goto endfunc;
                }

                arrayIndex += 1;
            }
        }

endfunc:

        CuFree (expected);
        return error;
    }

    return true;
}

