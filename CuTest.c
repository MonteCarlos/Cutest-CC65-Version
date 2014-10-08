
//#include <math.h>

#include "CuTest_internal.h"


/*-------------------------------------------------------------------------*
 * CuString
 *-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*
 * CuTest
 *-------------------------------------------------------------------------*/

void CuTestInit(CuTest* t, const char* name, TestFunction function)
{
	t->name = CuStrCopy(name);
	t->failed = 0;
	t->ran = 0;
	t->message = NULL;
	t->function = function;
	t->jumpBuf = NULL;
}

CuTest* CuTestNew(const char* name, TestFunction function)
{
	CuTest* tc = CU_ALLOC(CuTest);
	CuTestInit(tc, name, function);
	return tc;
}

void CuTestDelete(CuTest *t)
{
        if (!t) return;
        assert (NULL != t->name);
        free(t->name);
        //CuStringDelete(t->name);
        assert (NULL != t);
        free(t);
}

void CuTestRun(CuTest* tc)
{
	jmp_buf buf;
	tc->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		tc->ran = 1;
		(tc->function)(tc);


	}
	tc->jumpBuf = 0;
}

static void CuFailInternal(CuTest* tc, const char* file, int line, CuString* string)
{
	char* buf = (char*)calloc(HUGE_STRING_LEN, sizeof(char));
	assert (NULL != buf);
	sprintf(buf, "%s:%d: ", file, line);
	CuStringInsert(string, buf, 0);//buf is appended to string.

	//buf is not needed anymore
	free(buf);

	tc->failed = 1;
	tc->message = string->buffer;

	if (tc->jumpBuf != 0) longjmp(*(tc->jumpBuf), 0); //This breaks execution on true

	//This part is only reached if jumpBuf == NULL
}

void CuFail_Line(CuTest* tc, const char* file, int line, const char* message2, const char* message)
{
	CuString string;

	CuStringInit(&string);
	if (message2 != NULL)
	{
		CuStringAppend(&string, message2);
		CuStringAppend(&string, ": ");
	}
	CuStringAppend(&string, message);
	CuFailInternal(tc, file, line, &string);
}

void CuAssert_Line(CuTest* tc, const char* file, int line, const char* message, int condition)
{
	if (condition) return;
	CuFail_Line(tc, file, line, NULL, message);
}

void CuAssertStrEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
	const char* expected, const char* actual)
{
	CuString string;
	if ((expected == NULL && actual == NULL) ||
	    (expected != NULL && actual != NULL &&
	     strcmp(expected, actual) == 0))
	{
		return;
	}

	CuStringInit(&string);
	if (message != NULL)
	{
		CuStringAppend(&string, message);
		CuStringAppend(&string, ": ");
	}
	CuStringAppend(&string, "expected <");
	CuStringAppend(&string, expected);
	CuStringAppend(&string, "> but was <");
	CuStringAppend(&string, actual);
	CuStringAppend(&string, ">");
	CuFailInternal(tc, file, line, &string);
}

void CuAssertIntEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
	int expected, int actual)
{
	char* buf = (char*)calloc(STRING_MAX, sizeof(char));
	assert (NULL != buf);
	if (expected != actual){
		sprintf(buf, "expected <%d> but was <%d>", expected, actual);
		CuFail_Line(tc, file, line, message, buf);
	}
	free(buf);
}

/*void CuAssertDblEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
	double expected, double actual, double delta)
{
	char buf[STRING_MAX];
	if (fabs(expected - actual) <= delta) return;
	sprintf(buf, "expected <%f> but was <%f>", expected, actual);

	CuFail_Line(tc, file, line, message, buf);
}*/

void CuAssertPtrEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
	void* expected, void* actual)
{
	char* buf = calloc(STRING_MAX, sizeof(char));
	assert (NULL != buf);
	if (expected == actual) return;
	sprintf(buf, "expected pointer <0x%p> but was <0x%p>", expected, actual);
	CuFail_Line(tc, file, line, message, buf);
	assert (NULL != buf);
	free(buf);
}


/*-------------------------------------------------------------------------*
 * CuSuite
 *-------------------------------------------------------------------------*/

void CuSuiteInit(CuSuite* testSuite)
{
	testSuite->count = 0;
	testSuite->failCount = 0;
	testSuite->list = (CuTest**)calloc(MAX_TEST_CASES, sizeof(CuTest*));//alloc and zero fill
	assert (NULL != testSuite->list);
	//memset(testSuite->list, 0, sizeof(testSuite->list));
}

CuSuite* CuSuiteNew(void)
{
	CuSuite* testSuite = CU_ALLOC(CuSuite);
	CuSuiteInit(testSuite);
	return testSuite;
}

void CuSuiteDelete(CuSuite *testSuite)
{
        unsigned int n;
        assert (NULL != testSuite);
        for (n=0; n < MAX_TEST_CASES; n++)
        {
			//printf("%d\n",n);
                if (testSuite->list[n])
                {
                        CuTestDelete(testSuite->list[n]);
                        //assert (NULL != testSuite->list);
                        //free(testSuite->list);
                }
        }

        free(testSuite);
}

void CuSuiteAdd(CuSuite* testSuite, CuTest *testCase)
{
	assert(testSuite->count < MAX_TEST_CASES);
	testSuite->list[testSuite->count] = testCase;
	testSuite->count++;
}

void CuSuiteAddSuite(CuSuite* testSuite, CuSuite* testSuite2)
{
	int i;
	for (i = 0 ; i < testSuite2->count ; ++i)
	{
		CuTest* testCase = testSuite2->list[i];
		CuSuiteAdd(testSuite, testCase);
	}
}

void CuSuiteRun(CuSuite* testSuite)
{
	int i;
	CuTest* testCase = NULL;
	for (i = 0 ; i < testSuite->count ; ++i)
	{
		printf("%d:",i);
		testCase = testSuite->list[i];
		printf("%s\n",testCase->name);
		CuTestRun(testCase);
		if (testCase->failed) { testSuite->failCount += 1; }
	}
}

void CuSuiteSummary(CuSuite* testSuite, CuString* summary)
{
	int i;
	for (i = 0 ; i < testSuite->count ; ++i)
	{
		CuTest* testCase = testSuite->list[i];
		CuStringAppend(summary, testCase->failed ? "F" : ".");
	}
	CuStringAppend(summary, "\n\n");
}

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
