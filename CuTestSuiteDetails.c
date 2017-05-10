#include "CuTest_internal.h"

void CuSuiteDetails(CuSuite* testSuite, FILE* file)
{
 CuSize_t i;
 CuSize_t reported = 0;
    CuSize_t reportedFails = 0;
    CuSize_t reportedPasses = 0;
    CuSize_t testcount = CuSuiteGetTestcount(testSuite);
    CuSize_t failCount = CuSuiteGetFailcount(testSuite);
    CuSize_t passCount = testcount - failCount;
    CuSize_t memoryleaks = 0;

	register CuReport_t *report = testSuite->report;
    register CuTestPtr_t *testlist = testSuite->testlist;

	for (i = 0 ; i < testSuite->testcount ; ++i)
    {
        register CuTestPtr_t *testCase = &testlist[i];
        if (testCase->isSuite){
            CuSuiteDetails(testCase->suite, file);
        }else{
            register CuTest *test = testCase->test;
            if (test->failed)
            {
                CuTestFprintf(file, "Test failed: %s in %s\n", CuStringCStr(test->message), CuStringCStr(test->name));
                ++reportedFails;
            }else{
                ++reportedPasses;
            }
            if (test->memoryleak) ++memoryleaks;
            test->reported = true;
            ++reported;
        }
    }

    if (failCount == 0)
	{
		CuTestFprintf(file, "\n---OK---\n");
	}else{
	    CuTestFprintf(file, "\n!!!FAILURES!!!\n");
	}
	CuTestFormatReportString(report->reportStr, testcount, (size_t)(testcount-failCount), failCount, memoryleaks);

	if (testcount - failCount != passCount){
		CuTestFprintf(file, "Missed tests! #Registered(%u) > #Performed(%u)!\n", testcount, passCount);
	}
    /*f (reported - reportedFails != reportedPasses){
		CuTestFprintf(file, "Missed tests! #Registered(%u) > #Performed(%u)!\n", testSuite -> testcount, passCount);
	}*/
	assert(NULL != report);
	assert(CuAlloc_getBufferValidity(report));
	report -> reportedTests = reported;
	report -> reportedFails = reportedFails;
	report -> reportedPasses = reportedPasses;
	report -> performedTests = testcount;

	if (testSuite->ran) CuSuiteSummary(testSuite, file);
}
