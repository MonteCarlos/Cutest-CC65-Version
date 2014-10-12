#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest_internal.h"
static void X_CompareAsserts(CuTest* tc, const char *file, int line, const char* message, const char* expected, const char* actual);
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

void TestCuStringNew(CuTest* tc)
{
	CuString* str = CuStringNew();
	CuAssertTrue(tc, 0 == str->length);
	CuAssertTrue(tc, 0 != str->size);
	CuAssertStrEquals(tc, "", str->buffer);
}


void TestCuStringAppend(CuTest* tc)
{
	CuString* str = CuStringNew();
	CuStringAppend(str, "hello");
	CuAssertIntEquals(tc, 5, str->length);
	CuAssertStrEquals(tc, "hello", str->buffer);
	CuStringAppend(str, " world");
	CuAssertIntEquals(tc, 11, str->length);
	CuAssertStrEquals(tc, "hello world", str->buffer);
}


void TestCuStringAppendNULL(CuTest* tc)
{
	CuString* str = CuStringNew();
	CuStringAppend(str, NULL);
	CuAssertIntEquals(tc, 4, str->length);
	CuAssertStrEquals(tc, "NULL", str->buffer);
}


void TestCuStringAppendChar(CuTest* tc)
{
	CuString* str = CuStringNew();
	CuStringAppendChar(str, 'a');
	CuStringAppendChar(str, 'b');
	CuStringAppendChar(str, 'c');
	CuStringAppendChar(str, 'd');
	CuAssertIntEquals(tc, 4, str->length);
	CuAssertStrEquals(tc, "abcd", str->buffer);
}


void TestCuStringInserts(CuTest* tc)
{
	CuString* str = CuStringNew();
	CuStringAppend(str, "world");
	CuAssertIntEquals(tc, 5, str->length);
	CuAssertStrEquals(tc, "world", str->buffer);
	CuStringInsert(str, "hell", 0);
	CuAssertIntEquals(tc, 9, str->length);
	CuAssertStrEquals(tc, "hellworld", str->buffer);
	CuStringInsert(str, "o ", 4);
	CuAssertIntEquals(tc, 11, str->length);
	CuAssertStrEquals(tc, "hello world", str->buffer);
	CuStringInsert(str, "!", 11);
	CuAssertIntEquals(tc, 12, str->length);
	CuAssertStrEquals(tc, "hello world!", str->buffer);
}


void TestCuStringResizes(CuTest* tc)
{
	CuString* str = CuStringNew();
	int i;
	for(i = 0 ; i < STRING_MAX ; ++i)
	{
		CuStringAppend(str, "aa");
	}
	CuAssertTrue(tc, STRING_MAX * 2 == str->length);
	CuAssertTrue(tc, STRING_MAX * 2 <= str->size);
}

/*-------------------------------------------------------------------------*
 * Misc Test
 *-------------------------------------------------------------------------*/

void TestCuStrCopy(CuTest* tc)
{
	const char* old = "hello world";
	const char* newStr = CuStrCopy(old);
	CuAssert(tc, "old is new", strcmp(old, newStr) == 0);
}


void TestCuStringAppendFormat(CuTest* tc)
{
	int i;
	char* text = CuStrAlloc(301);		/* long string */
	CuString* str = CuStringNew();
	for (i = 0 ; i < 300 ; ++i)
		text[i] = 'a';
	text[300] = '\0';
	CuStringAppendFormat(str, "%s", text);

	/* buffer limit raised to HUGE_STRING_LEN so no overflow */

	CuAssert(tc, "length of str->buffer is 300", 300 == strlen(str->buffer));
}

void TestFail(CuTest* tc)
{
	jmp_buf buf;
	int pointReached = 0;
	CuTest* tc2 = CuTestNew("TestFails", zTestFails);
	tc2->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		CuFail(tc2, "hello world");
		pointReached = 1;
	}
	CuAssert(tc, "point was not reached", pointReached == 0);
}

void TestAssertStrEquals(CuTest* tc)
{
	jmp_buf buf;
	CuTest *tc2 = CuTestNew("TestAssertStrEquals", zTestFails);

	const char* expected = "expected <hello> but was <world>";
	const char *expectedMsg = "some text: expected <hello> but was <world>";

	tc2->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		CuAssertStrEquals(tc2, "hello", "world");
	}
	CuAssertTrue(tc, tc2->failed);
	//CompareAsserts(tc, "CuAssertStrEquals failed", expected, tc2->message);
	if (setjmp(buf) == 0)
	{
		CuAssertStrEquals_Msg(tc2, "some text", "hello", "world");
	}
	CuAssertTrue(tc, tc2->failed);
	//CompareAsserts(tc, "CuAssertStrEquals failed", expectedMsg, tc2->message);
}

void TestAssertStrEquals_NULL(CuTest* tc)
{
	jmp_buf buf;
	CuTest *tc2 = CuTestNew("TestAssertStrEquals_NULL", zTestFails);

	tc2->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		CuAssertStrEquals(tc2, NULL, NULL);
	}
	CuAssertTrue(tc, !tc2->failed);
	//compareasserts(tc, "CuAssertStrEquals_NULL failed", NULL, tc2->message);
	if (setjmp(buf) == 0)
	{
		CuAssertStrEquals_Msg(tc2, "some text", NULL, NULL);
	}
	CuAssertTrue(tc, !tc2->failed);
	//compareasserts(tc, "CuAssertStrEquals_NULL failed", NULL, tc2->message);
}

void TestAssertStrEquals_FailNULLStr(CuTest* tc)
{
	jmp_buf buf;
	CuTest *tc2 = CuTestNew("TestAssertStrEquals_FailNULLStr", zTestFails);

	const char* expected = "expected <hello> but was <NULL>";
	const char *expectedMsg = "some text: expected <hello> but was <NULL>";

	tc2->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		CuAssertStrEquals(tc2, "hello", NULL);
	}
	CuAssertTrue(tc, tc2->failed);
	//compareasserts(tc, "CuAssertStrEquals_FailNULLStr failed", expected, tc2->message);
	if (setjmp(buf) == 0)
	{
		CuAssertStrEquals_Msg(tc2, "some text", "hello", NULL);
	}
	CuAssertTrue(tc, tc2->failed);
	//compareasserts(tc, "CuAssertStrEquals_FailNULLStr failed", expectedMsg, tc2->message);
}

void TestAssertStrEquals_FailStrNULL(CuTest* tc)
{
	jmp_buf buf;
	CuTest *tc2 = CuTestNew("TestAssertStrEquals_FailStrNULL", zTestFails);

	const char* expected = "expected <NULL> but was <hello>";
	const char *expectedMsg = "some text: expected <NULL> but was <hello>";

	tc2->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		CuAssertStrEquals(tc2, NULL, "hello");
	}
	CuAssertTrue(tc, tc2->failed);
	//compareasserts(tc, "CuAssertStrEquals_FailStrNULL failed", expected, tc2->message);
	if (setjmp(buf) == 0)
	{
		CuAssertStrEquals_Msg(tc2, "some text", NULL, "hello");
	}
	CuAssertTrue(tc, tc2->failed);
	//compareasserts(tc, "CuAssertStrEquals_FailStrNULL failed", expectedMsg, tc2->message);
}

void TestAssertIntEquals(CuTest* tc)
{
	jmp_buf buf;
	CuTest *tc2 = CuTestNew("TestAssertIntEquals", zTestFails);
	const char* expected = "expected <42> but was <32>";
	const char* expectedMsg = "some text: expected <42> but was <32>";
	tc2->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		CuAssertIntEquals(tc2, 42, 32);
	}
	CuAssertTrue(tc, tc2->failed);
	//compareasserts(tc, "CuAssertIntEquals failed", expected, tc2->message);
	if (setjmp(buf) == 0)
	{
		CuAssertIntEquals_Msg(tc2, "some text", 42, 32);
	}
	CuAssertTrue(tc, tc2->failed);
	//compareasserts(tc, "CuAssertStrEquals failed", expectedMsg, tc2->message);
}


/*-------------------------------------------------------------------------*
 * main
 *-------------------------------------------------------------------------*/

CuSuite* CuGetSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, TestCuStrCopy);
	SUITE_ADD_TEST(suite, TestFail);
	SUITE_ADD_TEST(suite, TestAssertStrEquals);

	SUITE_ADD_TEST(suite, TestAssertStrEquals_NULL);
	//SUITE_ADD_TEST(suite, TestAssertStrEquals_FailStrNULL);
	//SUITE_ADD_TEST(suite, TestAssertStrEquals_FailNULLStr);

	return suite;
}

CuSuite* CuStringGetSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, TestCuStringNew);
	SUITE_ADD_TEST(suite, TestCuStringAppend);
	SUITE_ADD_TEST(suite, TestCuStringAppendNULL);
	SUITE_ADD_TEST(suite, TestCuStringAppendChar);
	SUITE_ADD_TEST(suite, TestCuStringInserts);
	SUITE_ADD_TEST(suite, TestCuStringResizes);
	SUITE_ADD_TEST(suite, TestCuStringAppendFormat);

	//alle OK

	return suite;
}

