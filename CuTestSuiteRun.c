#include "CuTest_internal.h"

// TODO (MyAcer#1#): find solution for messed output with sub tests
size_t CuSuiteRun(CuSuite* testSuite)
{
	size_t i,j, failCnt;
	unsigned long int pendingfrees;
	//CuTest* testCase = NULL;
	for (j = testSuite->testcount,i=0; j!=0; ++i,--j)
	{
		CuTestPtr_t *testCase = &(testSuite->testlist[i]);

		printf("%d: ",i);
		if (testCase->isSuite){
            if (failCnt = CuSuiteRun(testCase->suite)) return failCnt;
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

	return CuSuiteGetFailcount(testSuite);
}
