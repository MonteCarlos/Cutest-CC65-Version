#include "CuTest_internal.h"

// TODO (MyAcer#1#): find solution for messed output with sub tests
void CuSuiteRun(CuSuite* testSuite)
{
	size_t i;
	unsigned long int pendingfrees;
	CuTest* testCase = NULL;
	for (i = 0 ; i < testSuite->testcount ; ++i)
	{
		CuTestPtr_t *testCase = &(testSuite->testlist[i]);

		printf("%d:",i);
		if (testCase->isSuite){
            CuSuiteRun(testCase->suite);
		}else{
            register CuTest *test = testCase->test;

            fputs(CuStringCStr(test->name), stdout);

            pendingfrees = CuAlloc_getPendingFrees();
            CuTestRun(test);
            if (test->failed) {
                puts("->FAILED");
                testSuite->failCount += 1;
            }else{
                puts("->OK");
            }
            CuAssert(test, " Memory leak detected in \"", pendingfrees == CuAlloc_getPendingFrees());
            CuTestAppendMessage(test, "%s\". Pending frees before: %u, after: %u\n",
                            CuStringCStr(test->name), pendingfrees, CuAlloc_getPendingFrees());
		}
	}
}
