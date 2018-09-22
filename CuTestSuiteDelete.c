#include "CuTest_internal.h"

bool CuSuiteDelete(CuSuite_t *testSuite)
{
	if (testSuite){
        CuSize_t n = testSuite->totalcount;
        bool freereturn;
        CuTestOrSuitePtr_t *testlist = testSuite->testlist;

        //assert (NULL != testSuite);
        printf("Removing testcases:\n");

        //n may be 0 but then the loop is not executed
        for (; n >0; --n)
        {
            //We start with n=n_max and proceed to n=1. therefore index with n-1
            //We can assume here that n>0
			register CuTestOrSuitePtr_t *test = &testlist[n-1];

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
        freereturn = CuStringDelete(testSuite->name);
        assert(freereturn);
        freereturn = CuFree(testSuite);
        assert(freereturn);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
