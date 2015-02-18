#include "CuTest_internal.h"

// TODO (MyAcer#1#): find solution for messed output with sub tests
void CuSuiteRun(CuSuite* testSuite)
{
	int i;
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
            CuAssert(test, " Memory leak detected!", pendingfrees == CuAlloc_getPendingFrees());
		}
	}
}
