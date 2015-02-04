#include "CuTest_internal.h"

void CuSuiteDetails(CuSuite* testSuite, /*CuString* details*/ FILE* file)
{
	int i;
	int failCount = 0;

	if (testSuite->failCount == 0)
	{
		int passCount = testSuite->count - testSuite->failCount;
		const char* testWord = passCount == 1 ? "test" : "tests";
		fprintf(file, "OK (%d %s from %d)\n", passCount, testWord, testSuite->count);
		//CuStringAppendFormat(details, "OK (%d %s from %d)\n", passCount, testWord, testSuite->count);

		if (testSuite -> count != passCount){
			fprintf(file, "Missed tests! #Registered(%d) > #Performed(%d)!\n", testSuite -> count, passCount);
		}
	}
	else
	{
		if (testSuite->failCount == 1)
            fputs("There was 1 failure:\n", file);
			//CuStringAppend(details, "There was 1 failure:\n");
		else
            fprintf(file, "There were %d failures:\n", testSuite->failCount);
			//CuStringAppendFormat(details, "There were %d failures:\n", testSuite->failCount);

		for (i = 0 ; i < testSuite->count ; ++i)
		{
			CuTest* testCase = testSuite->list[i];
			if (testCase->failed)
			{
				failCount++;
                fprintf(file, "%s: %s\n", CuStringCStr(testCase->message), CuStringCStr(testCase->name));
				//CuStringAppendFormat(details, "%d) %s: %s\n",
					//failCount, testCase->name, CuStringCStr(testCase->message));
			}
		}
		fprintf(file, "\n!!!FAILURES!!!\n");
		//CuStringAppend(details, "\n!!!FAILURES!!!\n");
        fprintf(file,"Runs:%d, ",   testSuite->count);
        fprintf(file,"Passes:%d, ", testSuite->count - testSuite->failCount);
        fprintf(file,"Fails:%d\n",  testSuite->failCount);
		//CuStringAppendFormat(details, "Runs:%d, ",   testSuite->count);
		//CuStringAppendFormat(details, "Passes:%d, ", testSuite->count - testSuite->failCount);
		//CuStringAppendFormat(details, "Fails:%d\n",  testSuite->failCount);
	}
}
