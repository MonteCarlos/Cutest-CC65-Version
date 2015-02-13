#include "CuTest_internal.h"

void CuSuiteDelete(CuSuite *testSuite)
{
        long int n = testSuite->count-1;
        bool freereturn;

        assert (NULL != testSuite);
        printf("Removing testcases:\n");
        for (; n >=0; --n)
        {
			//printf("%d\n",n);

                if (testSuite->list[n])
                {
                        printf("%s\n",CuStringCStr(testSuite->list[n]->name));
                        CuTestDelete(testSuite->list[n]);
                        //assert (NULL != testSuite->list);
                        //free(testSuite->list);
                }
        }
        freereturn = CuFree(testSuite->list);
        assert(freereturn);
        freereturn = CuReportDestroy(testSuite->report);
        assert(freereturn);
        freereturn = CuFree(testSuite);
        assert(freereturn);
}
