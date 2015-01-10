#include "CuTest_internal.h"

void CuSuiteDetails(CuSuite* testSuite, CuString* details)
{
	int i;
	int failCount = 0;

	if (testSuite->failCount == 0)
	{
		int passCount = testSuite->count - testSuite->failCount;
		const char* testWord = passCount == 1 ? "test" : "tests";
		CuStringAppendFormat(details, "OK (%d %s from %d)\n", passCount, testWord, testSuite->count);

		if (testSuite -> count != passCount){
			printf("Missed tests! #Registered(%d) > #Performed(%d)!\n", testSuite -> count, passCount);
		}
	}
	else
	{
		if (testSuite->failCount == 1)
			CuStringAppend(details, "There was 1 failure:\n");
		else
			CuStringAppendFormat(details, "There were %d failures:\n", testSuite->failCount);

		for (i = 0 ; i < testSuite->count ; ++i)
		{
			CuTest* testCase = testSuite->list[i];
			if (testCase->failed)
			{
				failCount++;
				CuStringAppendFormat(details, "%d) %s: %s\n",
					failCount, testCase->name, testCase->message);
			}
		}
		CuStringAppend(details, "\n!!!FAILURES!!!\n");

		CuStringAppendFormat(details, "Runs:%d, ",   testSuite->count);
		CuStringAppendFormat(details, "Passes:%d, ", testSuite->count - testSuite->failCount);
		CuStringAppendFormat(details, "Fails:%d\n",  testSuite->failCount);
	}
}
