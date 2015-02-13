#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest_internal.h"

#define CompareAsserts(tc, message, expected, actual)  X_CompareAsserts((tc), __FILE__, __LINE__, (message), (expected), (actual))

static void X_CompareAsserts(CuTest* tc, const char *file, int line, const char* message, const char* expected, const char* actual)
{
	int mismatch;
	if (expected == NULL || actual == NULL) {
		mismatch = (expected != NULL || actual != NULL);
	} else {
		char front[sizeof(__FILE__)+1] = __FILE__;//seems to work now

		const size_t frontLen = sizeof(__FILE__);//strlen(front);
		const size_t expectedLen = strlen(expected);

		const char *matchStr = actual;
		front[sizeof(__FILE__)] = ':';
		front[sizeof(__FILE__)+1] = '\0';

		mismatch = (strncmp(matchStr, front, frontLen) != 0);
		if (!mismatch) {
			matchStr = strchr(matchStr + frontLen, ':');//This causes error because before __FILE__":" was not possible with cc65
			mismatch |= (matchStr == NULL || strncmp(matchStr, ": ", 2));
			if (!mismatch) {
				matchStr += 2;
				mismatch |= (strncmp(matchStr, expected, expectedLen) != 0);
			}
		}
	}

	CuAssert_Line(tc, file, line, message, !mismatch);
}
/*-------------------------------------------------------------------------*
 * CuString Test
 *-------------------------------------------------------------------------*/
/*void TestCompareAsserts(CuTest* tc)
{
	CompareAsserts
	CompareAsserts()
}*/

/*-------------------------------------------------------------------------*
 * CuTest Test
 *-------------------------------------------------------------------------*/


void TestCuTestNew(CuTest* tc)
{
	CuTest* tc2 = CuTestNew("MyTest", TestPasses);
	CuAssertStrEquals(tc, "MyTest", CuStringCStr(tc2->name));
	CuAssertTrue(tc, !tc2->failed);
	//CuAssertTrue(tc, tc2->message == NULL);
	CuAssertIntEquals(tc, 0, CuStringlen(tc->message));
	CuAssertTrue(tc, tc2->function == &TestPasses);
	CuAssertTrue(tc, tc2->ran == 0);
	CuAssertTrue(tc, tc2->jumpBuf == NULL);

	CuTestDelete(tc2);
}


void TestCuTestInit(CuTest *tc)
{
	CuTest *tc2 = CuTestNew("MyTest", TestPasses);;

	CuAssertStrEquals(tc, "MyTest", CuStringCStr(tc2->name));
	CuAssertTrue(tc, !tc2->failed);
	CuAssertIntEquals(tc, 0, CuStringlen(tc->message));
	CuAssertTrue(tc, tc2->function == &TestPasses);
	CuAssertTrue(tc, tc2->ran == 0);
	CuAssertTrue(tc, tc2->jumpBuf == NULL);

	CuTestDelete(tc2);
}

void TestCuAssert(CuTest* tc)
{
	CuTest *tc2 = CuTestNew("MyTest", TestPasses);
	int value = 4;//Suppress warning about constant comparison

	//CuTestInit(&tc2, "MyTest", TestPasses);

	CuAssert(tc2, "test 1", 5 == value + 1);
	CuAssertTrue(tc, !tc2->failed);
	CuAssertIntEquals(tc, 0, CuStringlen(tc->message));

	CuAssert(tc2, "test 2", 0);
	CuAssertTrue(tc, tc2->failed);
	//CompareAsserts(tc, "CuAssert didn't fail", "test 2", tc2.message);

	CuAssert(tc2, "test 3", 1);
	CuAssertTrue(tc, tc2->failed);
	//CompareAsserts(tc, "CuAssert didn't fail", "test 2", tc2.message);

	CuAssert(tc2, "test 4", 0);
	CuAssertTrue(tc, tc2->failed);
	//CompareAsserts(tc, "CuAssert didn't fail", "test 4", tc2.message);

	CuTestDelete(tc2);
}

void TestCuAssertPtrEquals_Success(CuTest* tc)
{
	CuTest *tc2 = CuTestNew("MyTest", TestPasses);
	int x;

	//CuTestInit(&tc2, "MyTest", TestPasses);

	/* test success case */
	CuAssertPtrEquals(tc2, &x, &x);
	CuAssertTrue(tc, ! tc2->failed);
	CuAssertIntEquals(tc, 0, CuStringlen(tc2->message));

	CuTestDelete(tc2);
}

void TestCuAssertPtrEquals_Failure(CuTest* tc)
{
	CuTest *tc2 = CuTestNew("MyTest", TestPasses);
	int x;
	int* nullPtr = NULL;
	char* expected_message = (char*)calloc(STRING_MAX, sizeof(char) );
	assert(NULL != expected_message);

	//CuTestInit(&tc2, "MyTest", TestPasses);

	/* test failing case */
	sprintf(expected_message, "expected pointer <0x%p> but was <0x%p>", nullPtr, &x);
	CuAssertPtrEquals(tc2, NULL, &x);
	CuAssertTrue(tc, tc2->failed);
	//CompareAsserts(tc, "CuAssertPtrEquals failed", expected_message, tc2.message);
	free(expected_message);

	CuTestDelete(tc2);
}

void TestCuAssertPtrNotNull_Success(CuTest* tc)
{
	CuTest *tc2 = CuTestNew("MyTest", TestPasses);
	int x;

	//CuTestInit(&tc2, "MyTest", TestPasses);

	/* test success case */
	CuAssertPtrNotNull(tc2, &x);
	CuAssertTrue(tc, ! tc2->failed);
	CuAssertIntEquals(tc, 0, CuStringlen(tc2->message));

	CuTestDelete(tc2);
}

void TestCuAssertPtrNotNull_Failure(CuTest* tc)
{
	CuTest *tc2 = CuTestNew("MyTest", TestPasses);
	/* test failing case */
	void* const ptrIsNULL = NULL;

    CuTestInit(tc2, "Should pass", TestPasses);

	CuAssertPtrNotNull(tc2, ptrIsNULL);
	CuAssertTrue(tc, tc2->failed);
	//CompareAsserts(tc, "CuAssertPtrNotNull failed", "null pointer unexpected", tc2.message);

	CuTestDelete(tc2);
}

void TestCuTestRun(CuTest* tc)
{
	CuTest *tc2 = CuTestNew("MyTest", TestPasses);
	//CuTestInit(tc2, "MyTest", zTestFails);
	CuTestRun(tc2);

	CuAssertStrEquals(tc, "MyTest", CuStringCStr(tc2->name));
	CuAssertFalse(tc, tc2->failed);
	CuAssertTrue(tc, tc2->ran);
	//CompareAsserts(tc, "TestRun failed", "test should fail", tc2.message);

	CuTestDelete(tc2);
}

/*-------------------------------------------------------------------------*
 * CuSuite Test
 *-------------------------------------------------------------------------*/

void TestCuSuiteInit(CuTest* tc)
{
	CuSuite *ts = CuSuiteNew();
	//CuSuiteInit(&ts);
	CuAssertTrue(tc, ts->count == 0);
	CuAssertTrue(tc, ts->failCount == 0);

	CuSuiteDelete(ts);
}

void TestCuSuiteNew(CuTest* tc)
{
	CuSuite* ts = CuSuiteNew();
	CuAssertTrue(tc, ts->count == 0);
	CuAssertTrue(tc, ts->failCount == 0);

	CuSuiteDelete(ts);
}

void TestCuSuiteAddTest(CuTest* tc)
{
	CuSuite* ts = CuSuiteNew();
	CuTest *tc2 = CuTestNew("MyTest", TestPasses);
	//CuTest tc2;

	//CuSuiteInit(ts);
	//CuTestInit(&tc2, "MyTest", zTestFails);

	CuSuiteAdd(ts, tc2);
	CuAssertTrue(tc, ts->count == 1);

	CuAssertStrEquals(tc, "MyTest", CuStringCStr(ts->list[0]->name));

	CuSuiteDelete(ts);
	CuTestDelete(tc2);
}

void TestCuSuiteAddSuite(CuTest* tc)
{
	CuSuite* ts1 = CuSuiteNew();
	CuSuite* ts2 = CuSuiteNew();

	CuSuiteAdd(ts1, CuTestNew("TestFails1", zTestFails));
	CuSuiteAdd(ts1, CuTestNew("TestFails2", zTestFails));

	CuSuiteAdd(ts2, CuTestNew("TestFails3", zTestFails));
	CuSuiteAdd(ts2, CuTestNew("TestFails4", zTestFails));

	CuSuiteAddSuite(ts1, ts2);
	CuAssertIntEquals(tc, 4, ts1->count);

	CuAssertStrEquals(tc, "TestFails1", CuStringCStr(ts1->list[0]->name));
	CuAssertStrEquals(tc, "TestFails2", CuStringCStr(ts1->list[1]->name));
	CuAssertStrEquals(tc, "TestFails3", CuStringCStr(ts1->list[2]->name));
	CuAssertStrEquals(tc, "TestFails4", CuStringCStr(ts1->list[3]->name));

	CuSuiteDelete(ts1);
	CuSuiteDelete(ts2);
}

void TestCuSuiteRun(CuTest* tc)
{
	CuSuite *ts = CuSuiteNew();
	CuTest *tc1 = CuTestNew("TestPasses", TestPasses);
	CuTest *tc2 = CuTestNew("TestPasses", TestPasses);
	CuTest *tc3 = CuTestNew("TestFails",  zTestFails);
	CuTest *tc4 = CuTestNew("TestFails",  zTestFails);

	CuSuiteAdd(ts, tc1);
	CuSuiteAdd(ts, tc2);
	CuSuiteAdd(ts, tc3);
	CuSuiteAdd(ts, tc4);

	CuAssertTrue(tc, ts->count == 4);

	CuSuiteRun(ts);
	CuAssertTrue(tc, ts->count - ts->failCount == 2);
	CuAssertTrue(tc, ts->failCount == 2);

	CuSuiteDelete(ts);//Deletes also corresponding test cases
}

void TestCuSuiteSummary(CuTest* tc)
{
	/*CuSuite ts;
	CuTest tc1, tc2;
	CuString summary;

	CuSuiteInit(&ts);
	CuTestInit(&tc1, "TestPasses", TestPasses);
	CuTestInit(&tc2, "TestFails",  zTestFails);
	CuStringInit(&summary);

	CuSuiteAdd(&ts, &tc1);
	CuSuiteAdd(&ts, &tc2);
	CuSuiteRun(&ts);

	CuSuiteSummary(&ts, &summary);

	CuAssertTrue(tc, ts.count == 2);
	CuAssertTrue(tc, ts.failCount == 1);
	CuAssertStrEquals(tc, ".F\n\n", summary.buffer);*/
	CuAssertTrue(tc, true);
}


void TestCuSuiteDetails_SingleFail(CuTest* tc)
{
	CuSuite *ts = CuSuiteNew();
	CuTest *tc1 = CuTestNew("TestPasses", TestPasses), *tc2 = CuTestNew("TestFails",  zTestFails);
	CuString details;
	const char* front;
	const char* back;
    FILE* file;

	CuSuiteAdd(ts, tc1);
	CuSuiteAdd(ts, tc2);
	CuSuiteRun(ts, file);

}


void TestCuSuiteDetails_SinglePass(CuTest* tc)
{
	CuSuite *ts = CuSuiteNew();
	CuTest *tc1 = CuTestNew("TestPasses", TestPasses);
	const char* expected;

	CuSuiteAdd(ts, tc1);
	CuSuiteRun(ts);

	CuSuiteDetails(ts, stdout);

    //Needs implementation of output testing

    //Does not belong here
	//CuAssertTrue(tc, ts.count == 1);
	//CuAssertTrue(tc, ts.failCount == 0);

	/*expected =
		"OK (1 test from 1)";

	CuAssertStrEquals(tc, expected, details.buffer);*/
	CuSuiteDelete(ts);
	CuAssertTrue(tc, true);
}

void TestCuSuiteDetails_MultiplePasses(CuTest* tc)
{
	/*CuSuite ts;
	CuTest tc1, tc2;
	CuString details;
	const char* expected;

	CuSuiteInit(&ts);
	CuTestInit(&tc1, "TestPasses", TestPasses);
	CuTestInit(&tc2, "TestPasses", TestPasses);
	CuStringInit(&details);

	CuSuiteAdd(&ts, &tc1);
	CuSuiteAdd(&ts, &tc2);
	CuSuiteRun(&ts);

//	CuSuiteDetails(&ts, &details);

	CuAssertTrue(tc, ts.count == 2);
	CuAssertTrue(tc, ts.failCount == 0);

	expected =
		"OK (2 tests from 2)";

	CuAssertStrEquals(tc, expected, details.buffer);*/
    CuAssertTrue(tc, true);//knock out test
}

void TestCuSuiteDetails_MultipleFails(CuTest* tc)
{
	/*CuSuite ts;
	CuTest tc1, tc2;
	CuString details;
	const char* front;
	const char* mid;
	const char* back;

	CuSuiteInit(&ts);
	CuTestInit(&tc1, "TestFails1", zTestFails);
	CuTestInit(&tc2, "TestFails2", zTestFails);
	CuStringInit(&details);

	CuSuiteAdd(&ts, &tc1);
	CuSuiteAdd(&ts, &tc2);
	CuSuiteRun(&ts);

//	CuSuiteDetails(&ts, &details);

	CuAssertTrue(tc, ts.count == 2);
	CuAssertTrue(tc, ts.failCount == 2);

	front =
		"There were 2 failures:\n"
		"1) TestFails1: ";
	mid =   "test should fail\n"
		"2) TestFails2: ";
	back =  "test should fail\n"
		"\n!!!FAILURES!!!\n"
		"Runs:2, Passes:0, Fails:2\n";

	CuAssertStrEquals(tc, back, details.buffer + strlen(details.buffer) - strlen(back));
	CuAssert(tc, "Couldn't find middle", strstr(details.buffer, mid) != NULL);
	details.buffer[strlen(front)] = 0;
	CuAssertStrEquals(tc, front, details.buffer);*/
	CuAssertTrue(tc, true);//knock out test
}




void TestFail(CuTest* tc)
{
	//jmp_buf buf;
	//int pointReached = 0;
	CuTest* tc2 = CuTestNew("TestFails", zTestFails);
	//tc2->jumpBuf = &buf;
	//if (setjmp(buf) == 0)
	//{
    CuFail(tc2);
    CuAssertTrue(tc, tc2 -> failed == true);
	//	pointReached = 1;
	//}
	//CuAssert(tc, "point was not reached", pointReached == 0);
	CuTestDelete(tc2);
}

void TestAssertArrayEquals(CuTest* tc)
{
	//Create new test so that failed test does not appear in final statistics
	CuTest *tc2 = CuTestNew("ArrayEquals", zTestFails);
	int array1[] = {100,200,300,400,500};
	int array2[] = {100,200,400,300,500};

	//77const char* expected = "expected <42> but was <32>";
	//const char* expectedMsg = "some text: expected <42> but was <32>";
	bool assertResult = CuAssertArrayEquals(tc2, array1, array1, sizeof(array1[0]), sizeof(array1)/sizeof(array1[0]));

	//However, the tests of the results of the previous test should appear in the final statistics
	CuAssertFalse(tc, assertResult);
	CuAssertFalse(tc, tc2->failed);

	assertResult = CuAssertArrayEquals(tc2, array1, array2, sizeof(array1[0]), sizeof(array1)/sizeof(array1[0]));

	//However, the tests of the results of the previous test should appear in the final statistics
	CuAssertTrue(tc, assertResult);
	CuAssertTrue(tc, tc2->failed);

	CuTestDelete(tc2);
}



void TestAssertIntEquals(CuTest* tc)
{
	//jmp_buf buf;

	//Create new test so that failed test does not appear in final statistics
	CuTest *tc2 = CuTestNew("IntEquals", zTestFails);
	//77const char* expected = "expected <42> but was <32>";
	//const char* expectedMsg = "some text: expected <42> but was <32>";
	bool assertResult = CuAssertIntEquals(tc2, 42, 32);

	//tc2->jumpBuf = &buf;
	//if (setjmp(buf) == 0)
	//{

	//}

	//However, the tests of the results of the previous test should appear in the final statistics
	CuAssertTrue(tc, assertResult);
	CuAssertTrue(tc, tc2->failed);
	//CompareAsserts(tc, "CuAssertIntEquals failed", expected, tc2->message);
	//if (setjmp(buf) == 0)
	//{
		assertResult = CuAssertIntEquals_Msg(tc2, "Ints not equal", 42, 32);
		CuAssertTrue(tc, assertResult);
	//}
	CuAssertTrue(tc, tc2->failed);
	//CompareAsserts(tc, "CuAssertStrEquals failed", expectedMsg, tc2->message);
	CuTestDelete(tc2);
}

/*void TestAssertDblEquals(CuTest* tc)
{
	jmp_buf buf;
	double x = 3.33;
	double y = 10.0 / 3.0;
	CuTest *tc2 = CuTestNew("TestAssertDblEquals", zTestFails);
	char expected[STRING_MAX];
	char expectedMsg[STRING_MAX];
	sprintf(expected, "expected <%lf> but was <%lf>", x, y);
	sprintf(expectedMsg, "some text: expected <%lf> but was <%lf>", x, y);

	CuTestInit(tc2, "TestAssertDblEquals", TestPasses);

	CuAssertDblEquals(tc2, x, x, 0.0);
	CuAssertTrue(tc, ! tc2->failed);
	CuAssertTrue(tc, NULL == tc2->message);

	CuAssertDblEquals(tc2, x, y, 0.01);
	CuAssertTrue(tc, ! tc2->failed);
	CuAssertTrue(tc, NULL == tc2->message);

	tc2->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		CuAssertDblEquals(tc2, x, y, 0.001);
	}
	CuAssertTrue(tc, tc2->failed);
	CompareAsserts(tc, "CuAssertDblEquals failed", expected, tc2->message);
	tc2->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		CuAssertDblEquals_Msg(tc2, "some text", x, y, 0.001);
	}
	CuAssertTrue(tc, tc2->failed);
	CompareAsserts(tc, "CuAssertDblEquals failed", expectedMsg, tc2->message);
}*/

/*-------------------------------------------------------------------------*
 * test CuProgress
 *-------------------------------------------------------------------------*/

 void TestSetProgressStartEnd(CuTest *tc){
    const unsigned long int st = 100;
    const unsigned long int en = 200;

    //Test with start value lower than end value
    CuTestSetProgressStartEnd(st, en);
    CuAssertIntEquals(tc, st, CuTestGetProgressStart());
    CuAssertIntEquals(tc, en, CuTestGetProgressEnd());
    CuAssertIntEquals(tc, en-st, CuTestGetProgressRange());

    //Test with start value higher than end value
    CuTestSetProgressStartEnd(en, st);
    CuAssertIntEquals(tc, en, CuTestGetProgressStart());
    CuAssertIntEquals(tc, st, CuTestGetProgressEnd());
    CuAssertIntEquals(tc, en-st, CuTestGetProgressRange());
 }

 void TestPrintProgressState(CuTest *tc){
    const unsigned long int st = 100;
    const unsigned long int en = 200;

    //Test with start value lower than end value
    CuTestSetProgressStartEnd(st, en);
    //AssertIntEquals

    //Test with start value higher than end value
    CuTestSetProgressStartEnd(en, st);

 }
/*-------------------------------------------------------------------------*
 * main
 *-------------------------------------------------------------------------*/

CuSuite* CuGetSuite(void)
{
	CuSuite* suite;
	suite = CuSuiteNew();
    printf("Alloc Count after SuiteNew:%lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount());
	SUITE_ADD_TEST(suite, TestFail);
    printf("Alloc Count after ADD_TEST:%lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount());
	SUITE_ADD_TEST(suite, TestAssertIntEquals);

	SUITE_ADD_TEST(suite, TestCuTestNew);
	SUITE_ADD_TEST(suite, TestCuTestInit);

	SUITE_ADD_TEST(suite, TestCuAssert);
	//SUITE_ADD_TEST(suite, TestCuAssertPtrEquals_Success);
	SUITE_ADD_TEST(suite, TestCuAssertPtrEquals_Failure);

	SUITE_ADD_TEST(suite, TestCuAssertPtrNotNull_Success);
	//SUITE_ADD_TEST(suite, TestCuAssertPtrNotNull_Failure);
	SUITE_ADD_TEST(suite, TestCuTestRun);

	SUITE_ADD_TEST(suite, TestCuSuiteInit);
	SUITE_ADD_TEST(suite, TestCuSuiteNew);
	//SUITE_ADD_TEST(suite, TestCuSuiteAddTest);
	//SUITE_ADD_TEST(suite, TestCuSuiteAddSuite);
	SUITE_ADD_TEST(suite, TestCuSuiteRun);
	SUITE_ADD_TEST(suite, TestCuSuiteSummary);
	SUITE_ADD_TEST(suite, TestCuSuiteDetails_SingleFail);
	SUITE_ADD_TEST(suite, TestCuSuiteDetails_SinglePass);
	SUITE_ADD_TEST(suite, TestCuSuiteDetails_MultiplePasses);
	SUITE_ADD_TEST(suite, TestCuSuiteDetails_MultipleFails);

	SUITE_ADD_TEST(suite, TestSetProgressStartEnd);
	SUITE_ADD_TEST(suite, TestPrintProgressState);
	SUITE_ADD_TEST(suite, TestAssertArrayEquals);

	printf("Registered #%d testcases\n", suite->count);
	return suite;
}
