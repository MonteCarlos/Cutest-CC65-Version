#include "CuTest_internal.h"
#include <signal.h>


CuTest *test = NULL;
CuSuite *suite = NULL;

static void abrtSignalHandler(int sig){
    puts("\n!!! Exception occured in CuSuiteRun. Aborted.");

    if (suite){
        printf("!!! Suite: \"%s\"\n", CuStringCStr(suite->name));
    }
	if (test){
        printf("!!! TestCase: \"%s\"\n", CuStringCStr(test->name));
	}
}

// Workaround default signal handler for SIGSEGV by calling abort and eventually call hooked abort handler
static void illSignalHandler(int sig){
    abort();
}

// TODO (MyAcer#1#): find solution for messed output with sub tests CuSize_t CuSuiteRun(CuSuite* testSuite)
CuSize_t CuSuiteRun(CuSuite* testSuite)
{
	__sighandler_t prevHandler = signal(SIGSEGV, illSignalHandler);
    __sighandler_t prevHandler2 = signal(SIGABRT, abrtSignalHandler);

	if (testSuite){
		CuSize_t i,j, failCnt;
		CuSize_t pendingfrees;

        suite = testSuite;
		//CuTest* testCase = NULL;
		for (j = testSuite->totalcount,i=0; j!=0; ++i,--j)
		{
			CuTestPtr_t *testCase = &(testSuite->testlist[i]);
			//signal(SIGSEGV, illSignalHandler);
			printf("%u: ",i);
			if (testCase->isSuite){
				if ( (failCnt = CuSuiteRun(testCase->suite) ) ) testSuite->failCount+=failCnt;
			}else{
				test = testCase->test;

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

		signal(SIGSEGV, prevHandler);
		signal(SIGABRT, prevHandler2);
		return CuSuiteGetFailcount(testSuite);
	}
	return ~0;
}
