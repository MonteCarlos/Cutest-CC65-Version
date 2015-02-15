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
	CuReport_t *report = testSuite->report;

	if (failCount == 0)
	{
		CuTestFprintf(file, "OK");

		reported = reportedPasses = testcount;
	}
	else
	{
		for (i = 0 ; i < testSuite->count ; ++i)
		{
			CuTest* testCase = testSuite->list[i];
			if (testCase->failed)
			{
				failCount++;
                CuTestFprintf(file, "%s: %s\n", CuStringCStr(testCase->message), CuStringCStr(testCase->name));
	            ++reportedFails;
			}else{
                ++reportedPasses;
            }
			testCase->reported = true;
			++reported;
		}
		CuTestFprintf(file, "\n!!!FAILURES!!!\n");
	}

	CuTestFormatReportString(report->reportStr, testcount, testcount-failCount, failCount);

	if (testSuite -> count - testSuite->failCount != passCount){
		CuTestFprintf(file, "Missed tests! #Registered(%u) > #Performed(%u)!\n", testSuite -> count, passCount);
	}

	assert(NULL != report);
	assert(CuAlloc_getBufferValidity(report));
	report -> reportedTests = reported;
	report -> reportedFails = reportedFails;
	report -> reportedPasses = reportedPasses;
	report -> performedTests = testcount;
}
