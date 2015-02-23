#include "CuTest_internal.h"

void CuSuiteDelete(CuSuite *testSuite)
{
        long int n = testSuite->testcount-1;
        bool freereturn;
        CuTestPtr_t *testlist = testSuite->testlist;

        assert (NULL != testSuite);
        printf("Removing testcases:\n");
        for (; n >=0; --n)
        {
			register CuTestPtr_t *test = &testlist[n];

            if (NULL!=test->test)
            {
                if (test->isSuite){
                    CuSuiteDelete(test->suite);
                }else{
                    printf("%s\n",CuStringCStr(test->test->name));
                    CuTestDelete(test->test);
                    //assert (NULL != testSuite->list);
                    //free(testSuite->list);
                }
            }
        }


        freereturn = CuFree(testlist);
        assert(freereturn);
        freereturn = CuReportDestroy(testSuite->report);
        assert(freereturn);
        freereturn = CuFree(testSuite);
        assert(freereturn);
}
