#include "CuTest_internal.h"
size_t my_fprintf(FILE* file, char* format, ...){
	va_list va;
	va_start(va, format);

	if (NULL != file){
		vfprintf(file, format, va);
	}
	va_end(va);
}

void CuSuiteDetails(CuSuite* testSuite, FILE* file)
{
	size_t i;
	size_t reported = 0;
    size_t reportedFails = 0;
    size_t reportedPasses = 0;
    size_t testcount = CuSuiteGetTestcount(testSuite);
    size_t failCount = CuSuiteGetFailcount(testSuite);
	CuReport_t *report = testSuite->report;

	if (failCount == 0)
	{
		size_t passCount = testcount - failCount;
		const char* plural_s = passCount == 1 ? "" : "s";
		my_fprintf(file, "OK (%u test%s from %u)\n", passCount, plural_s, testSuite->count);
		//CuStringAppendFormat(details, "OK (%d %s from %d)\n", passCount, testWord, testSuite->count);

		if (testSuite -> count != passCount){
			my_fprintf(file, "Missed tests! #Registered(%u) > #Performed(%u)!\n", testSuite -> count, passCount);
		}
		reported = reportedPasses = testcount;
	}
	else
	{
		/*char* isWasOrWere = "was";
		char* plural_s = "";//empty string->singular

		if (failCount  > 1){
            isWasOrWere = "were";
            plural_s = "s";
		}*/

        my_fprintf(file, "\n!!!FAILURES!!!\n");
		//my_fprintf(file, "There %s %u failure%s", isWasOrWere, failCount , plural_s);

		for (i = 0 ; i < testSuite->count ; ++i)
		{
			CuTest* testCase = testSuite->list[i];
			if (testCase->failed)
			{
				failCount++;
                my_fprintf(file, "%s: %s\n", CuStringCStr(testCase->message), CuStringCStr(testCase->name));
	            ++reportedFails;
			}else{
                ++reportedPasses;
            }
			testCase->reported = true;
			++reported;
		}

        my_fprintf(file,"Runs:%u, Passes:%u, Fails:%u\n", testcount, testcount-failCount, failCount);
	}

	assert(NULL != report);
	assert(CuAlloc_getBufferValidity(report));
	report -> reportedTests = reported;
	report -> reportedFails = reportedFails;
	report -> reportedPasses = reportedPasses;
	report -> performedTests = testcount;
}
