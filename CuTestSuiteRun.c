#include "CuTest_internal.h"

// TODO (MyAcer#1#): find solution for messed output with sub tests
void CuSuiteRun(CuSuite* testSuite)
{
	int i;
	unsigned long int pendingfrees;
	CuTest* testCase = NULL;
	for (i = 0 ; i < testSuite->count ; ++i)
	{
		printf("%d:",i);
		testCase = testSuite->list[i];
		fputs(CuStringCStr(testCase->name), stdout);

		pendingfrees = CuAlloc_getPendingFrees();
		CuTestRun(testCase);
		if (testCase->failed) {
			puts("->FAILED");
			testSuite->failCount += 1;
		}else{
			puts("->OK");
		}
		CuAssert(testCase, " Memory leak detected!", pendingfrees = CuAlloc_getPendingFrees());
	}

    //Run other suites in test
	for (i = 0; i< testSuite->suitecount; ++i){
        CuSuiteRun(testSuite->suitelist[i]);
	}
}
