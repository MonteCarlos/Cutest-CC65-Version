#include "CuTest_internal.h"

void CuSuiteDetails(CuSuite* testSuite, FILE* file)
{
	size_t i;
	size_t reported = 0;
    size_t reportedFails = 0;
    size_t reportedPasses = 0;
    size_t testcount = CuSuiteGetTestcount(testSuite);
    size_t failCount = CuSuiteGetFailcount(testSuite);
    size_t passCount = testcount - failCount;
	register CuReport_t *report = testSuite->report;
    register CuTestPtr_t *testlist = testSuite->testlist;

	for (i = 0 ; i < testSuite->testcount ; ++i)
    {
        CuTestPtr_t testCase = testlist[i];
        if (testCase.isSuite){
            CuSuiteDetails(testCase.suite, file);
        }else{
            register CuTest *test = testCase.test;
            if (test->failed)
            {
                CuTestFprintf(file, "%s: %s\n", CuStringCStr(test->message), CuStringCStr(test->name));
                ++reportedFails;
            }else{
                ++reportedPasses;
            }
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
	CuTestFormatReportString(report->reportStr, testcount, testcount-failCount, failCount);

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

	CuSuiteSummary(testSuite, file);
}
