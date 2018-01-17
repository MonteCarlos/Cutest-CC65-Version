#include "CuTest_internal.h"
#include <signal.h>

/*static void illSignalHandler(int sig){
	printf("!!! Exception occured in CuSuiteRun. Signal %d !!!\n\n", sig);
	signal(SIGSEGV, SIG_IGN);
}*/

// TODO (MyAcer#1#): find solution for messed output with sub tests CuSize_t CuSuiteRun(CuSuite* testSuite)
CuSize_t CuSuiteRun(CuSuite* testSuite)
{
	//__sighandler_t prevHandler = signal(SIGSEGV, illSignalHandler);

	if (testSuite){
		CuSize_t i,j, failCnt;
		CuSize_t pendingfrees;
		//CuTest* testCase = NULL;
		for (j = testSuite->totalcount,i=0; j!=0; ++i,--j)
		{
			CuTestPtr_t *testCase = &(testSuite->testlist[i]);
			//signal(SIGSEGV, illSignalHandler);
			printf("%u: ",i);
			if (testCase->isSuite){
				if ( failCnt = CuSuiteRun(testCase->suite) ) testSuite->failCount+=failCnt;
			}else{
				register CuTest *test = testCase->test;

				/*if (test->setup) {
					test->setup(test->vaargs1);
				}*/
				fputs(CuStringCStr(test->name), stdout);
				fputc(' ',stdout);
				pendingfrees = CuAlloc_getPendingFrees();
				CuTestRun(test);
				if (test->failed) {
					puts("->FAILED");
					puts(CuStringCStr(test->message));
					testSuite->failCount += 1;
				}else{
					puts("->OK");
				}
				if ( CuAssert(test, " Memory leak detected (", pendingfrees == CuAlloc_getPendingFrees()) ){
					CuTestAppendMessage(test, "Pending frees before: %u, after: %u)",
						pendingfrees, CuAlloc_getPendingFrees()
					);
					test->memoryleak = true;
				}
				/*
				if (test->teardown){
					test->teardown(test->vaargs2);
				}*/
			}
		}
		if(!i){fputs("Suite contains no tests", stdout);}
		testSuite->ran = true;

		//signal(SIGSEGV, prevHandler);
		return CuSuiteGetFailcount(testSuite);
	}
	return ~0;
}
