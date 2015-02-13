#include "CuTest_internal.h"

void CuSuiteDetails(CuSuite* testSuite, /*CuString* details*/ FILE* file, CuReport_t *report)
{
	size_t i;
	size_t reported = 0;
    size_t reportedFails = 0;
    size_t reportedPasses = 0;
    size_t testcount = CuSuiteGetTestCount(testSuite);
    size_t failCount = CuSuiteGetFailcount(testSuite);

	if (failCount == 0)
	{
		size_t passCount = testcount - failCount;
		const char* plural_s = passCount == 1 ? "" : "s";
		fprintf(file, "OK (%u test%s from %u)\n", passCount, plural_s, testSuite->count);
		//CuStringAppendFormat(details, "OK (%d %s from %d)\n", passCount, testWord, testSuite->count);

		if (testSuite -> count != passCount){
			fprintf(file, "Missed tests! #Registered(%u) > #Performed(%u)!\n", testSuite -> count, passCount);
		}
	}
	else
	{
		/*char* isWasOrWere = "was";
		char* plural_s = "";//empty string->singular

		if (failCount  > 1){
            isWasOrWere = "were";
            plural_s = "s";
		}*/

        fprintf(file, "\n!!!FAILURES!!!\n");
		//fprintf(file, "There %s %u failure%s", isWasOrWere, failCount , plural_s);

		for (i = 0 ; i < testSuite->count ; ++i)
		{
			CuTest* testCase = testSuite->list[i];
			if (testCase->failed)
			{
				failCount++;
                fprintf(file, "%s: %s\n", CuStringCStr(testCase->message), CuStringCStr(testCase->name));
	            ++reportedFails;
			}else{
                ++reportedPasses;
            }
			testCase->reported = true;
			++reported;
		}

        fprintf(file,"Runs:%u, Passes:%u, Fails:%u\n", testcount, testcount-failCount, failCount);
	}
}
