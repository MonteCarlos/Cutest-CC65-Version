#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CutestString_internal.h"
#include "CuTest_internal.h"
static void X_CompareAsserts(CuTest* tc, const char *file, int line, const char* message, const char* expected, const char* actual);
#define CompareAsserts(tc, message, expected, actual)  X_CompareAsserts((tc), __FILE__, __LINE__, (message), (expected), (actual))

char thisfile[] = __FILE__;

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
	CuAssertTrue(tc, CuAlloc_getBufferValidity(str));
	CuAssertTrue(tc, CUSTRING_LEN_NEW == CuAlloc_getDataSize(str));
	CuAssertTrue(tc, 0 == str->length);
	CuAssertTrue(tc, CUSTRING_LEN_NEW == str->size);
	CuAssertStrEquals(tc, "", str->buffer);
	CuStringDelete(str);
}

void TestCuStringInit(CuTest* tc)
{
	CuString* str = CuStringNew();
	CuStringAppend("this string is more than sixtifour letters long, which is now true!");
    CuFree(str->buffer);
    CuStringInit(str);

	CuAssertTrue(tc, CuAlloc_getBufferValidity(str));
	CuAssertTrue(tc, CUSTRING_LEN_NEW == CuAlloc_getDataSize(str));
	CuAssertTrue(tc, 0 == str->length);
	CuAssertTrue(tc, CUSTRING_LEN_NEW == str->size);
	CuAssertStrEquals(tc, "", str->buffer);
	CuStringDelete(str);
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
	CuStringDelete(str);
}


void TestCuStringAppendNULL(CuTest* tc)
{
	CuString* str = CuStringNew();
	CuStringAppend(str, NULL);
	CuAssertIntEquals(tc, 4, str->length);
	CuAssertStrEquals(tc, "NULL", str->buffer);
	CuStringDelete(str);
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
	CuStringDelete(str);
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
	CuStringDelete(str);
}


void TestCuStringResizes(CuTest* tc)
{
	CuString* str = CuStringNew();
	int i;
	for(i = 0 ; i < CUSTRING_LEN_NEW ; ++i)
	{
		CuStringAppend(str, "aa");
	}
	CuAssertTrue(tc, CUSTRING_LEN_NEW * 2 == str->length);
	CuAssertTrue(tc, CUSTRING_LEN_NEW * 2 <= str->size);
	CuStringDelete(str);
}

/*-------------------------------------------------------------------------*
 * Misc Test
 *-------------------------------------------------------------------------*/

void TestCuStrCopy(CuTest* tc)
{
	const char* old = "hello world";
	char* newStr = CuStrCopy(old);
	CuAssertTrue(tc, strcmp(old, newStr) == 0);
	CuFree(newStr);
}


void TestCuStrAlloc(CuTest* tc)
{
    CuStringSize_t size = 10;
	char* ptr = CuStrAlloc(size);
	CuAssertTrue(tc, CuAlloc_getBufferValidity(ptr));
	CuAssertIntEquals(tc, CuAlloc_getDataSize(ptr), size+1);
    CuFree(ptr);
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
	CuStringDelete(str);
	CuFree(text);

}

// TODO (MyAcer#1#): strEquals functions belong in CuTest not CuString
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
	CuTestDelete(tc2);
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
	CuTestDelete(tc2);
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
	CuTestDelete(tc2);
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
	CuTestDelete(tc2);
}

void TestCuStringLen(CuTest *tc){
	char *teststr = "My test string";
	CuString *str = CuStringConvertCStr(teststr);

	CuAssertIntEquals( tc, CuStringLen(str), strlen(teststr) );
	CuStringDelete(str);
}

// TODO (Stefan#1#): Implement test case!
void TestCuStringClear(CuTest* tc){

}

void TestCuStringSize(CuTest *tc){
	char *teststr = "Another test string";
	CuString *str = CuStringConvertCStr(teststr);
	CuStringResize(str, strlen(teststr));
	CuAssertIntEquals( tc, CuStringSize(str), strlen(teststr) );
	CuStringDelete(str);
}

void TestCuStringCStr(CuTest *tc){
	CuString *str = CuStringNew();
	const char *desiredStr = "This is a test.";
	//CuStringInit(&str);
	CuStringAppend(str, desiredStr);
	CuAssertStrEquals(tc,
					(const char*)CuStringCStr(str),
					(const char*)desiredStr);
					//check string content
	CuAssertIntEquals( tc, strlen(desiredStr), str->length );//check length of string up to \0
	CuAssertIntEquals( tc, CUSTRING_LEN_NEW, str->size );//check occupied memory
	CuStringDelete(str);
}

void TestCuStringAppendLineFile(CuTest *tc){
	char frontStr[] = "This file is: ";
	unsigned long line = __LINE__;
    CuString* thisline = CuStringNew();
    char *expected;
	CuString *str = CuStringConvertCStr(frontStr);
	CuStringAppendULong(thisline, line);
	expected = malloc(sizeof(frontStr)+sizeof(thisfile)+strlen(CuStringCStr(thisline))+2+1);
	CuStringAppendLineFile(str, thisfile, line);
	strcpy(expected, frontStr);
	strcat(expected, thisfile);
	strcat(expected, "(");
	strcat(expected, CuStringCStr(thisline));
	strcat(expected, ")");

	CuAssertStrEquals(tc, expected, CuStringCStr(str));
	free(expected);
	CuStringDelete(str);
	CuStringDelete(thisline);
}
void TestCuStringAppendISvsNOT(CuTest *tc){
    enum {TestISvsNOT_MAXSTRLEN = 100};

    int desired = 100, actual = 103;
    char* leadstr = "Inttest: ";
    CuString *str = CuStringConvertCStr(leadstr);
    char* tempstr = malloc(TestISvsNOT_MAXSTRLEN);

    CuStringAppendISvsNOT(str, "%d", desired, actual);
    snprintf(tempstr, TestISvsNOT_MAXSTRLEN, "%sis \"%d\" not \"%d\"", leadstr, desired, actual);
    CuAssertStrEquals(tc, tempstr, CuStringCStr(str));

    free(tempstr);
    CuStringDelete(str);
}

/*void TestCuStringComposeMessage(CuTest *tc){
	char* msgpart1 = "First msg";
	char* msgpart2 = "Second msg";
	unsigned long int thisline = __LINE__;
	CuString *thislineStr = CuStringNew();
	CuString *msg = CuStringNew();
	char* expected = malloc(strlen(msgpart1)+strlen(msgpart2)+strlen(thisfile)+21);
	assert(NULL != expected);

	CuStringAppendULong(thislineStr, thisline);
	CuStringComposeMessage(msg, msgpart1, msgpart2, thisfile, thisline);
	sprintf(expected, "%s: %s\n%s(%lu)", msgpart1, msgpart2, thisfile, thisline);
	CuAssertStrEquals(tc, expected, CuStringCStr(msg));

	CuStringComposeMessage(msg, NULL, msgpart2, thisfile, thisline);
	sprintf(expected, "NULL: %s\n%s(%lu)", msgpart2, thisfile, thisline);
	CuAssertStrEquals(tc, expected, CuStringCStr(msg));

	CuStringComposeMessage(msg, NULL, NULL, thisfile, thisline);
	sprintf(expected, "NULL\n%s(%lu)", thisfile, thisline);
	CuAssertStrEquals(tc, expected, CuStringCStr(msg));

	CuStringComposeMessage(msg, msgpart1, NULL, thisfile, thisline);
	sprintf(expected, "%s\n%s(%lu)", msgpart1, thisfile, thisline);
	CuAssertStrEquals(tc, expected, CuStringCStr(msg));
	free(expected);
}
*/
void TestCuStringAppendULong(CuTest *tc){
	unsigned long int num = 1234567890;
	char* numStr = "1234567890";

	CuString *str = CuStringNew();
	CuStringAppendULong(str, num);
	CuAssertStrEquals(tc, numStr, CuStringCStr(str));
	CuStringDelete(str);
}

void TestCuStringConvertCStr(CuTest *tc){
	char* testtext = "This is my testtext.";
	CuString *str = CuStringConvertCStr(testtext);
	CuAssertStrEquals(tc, testtext, CuStringCStr(str));
	CuAssertIntEquals(tc, CuStringLen(str), strlen(testtext));
	CuAssertIntEquals(tc, CuStringSize(str), CUSTRING_LEN_NEW);
	testtext = NULL;
	CuStringDelete(str);

	str = CuStringConvertCStr(testtext);
	CuAssertStrEquals(tc, "NULL", CuStringCStr(str));
	CuStringDelete(str);
}

bool helper_TestCuStringAppendVariadicFormat(CuString *str, char* format, ...){
    va_list va;

    va_start(va, format);
    CuStringAppendVariadicFormat(str, format, va);
    va_end(va);
    return false;
}

void TestCuStringAppendVariadicFormat(CuTest *tc){
    int myInt = -543;
    char* myStr = "test!";
    char myChar = '#';

	char* format = "Int:%d, Str:%s, Char:%c";
	CuString *str = CuStringNew();
	CuString *str2 = CuStringNew();

	bool err = helper_TestCuStringAppendVariadicFormat(str, format, myInt, myStr, myChar);
	CuStringAppendFormat(str2, format, myInt, myStr, myChar);

	CuAssertStrEquals(tc, CuStringCStr(str2), CuStringCStr(str));
    CuAssertFalse(tc, err);

	CuStringDelete(str);
	CuStringDelete(str2);
}

/*-------------------------------------------------------------------------*
 * main
 *-------------------------------------------------------------------------*/

CuSuite* CuStringGetSuite1(void)
{
	CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestCuStrAlloc);
    SUITE_ADD_TEST(suite, TestCuStrCopy);
    SUITE_ADD_TEST(suite, TestCuStringNew);
    SUITE_ADD_TEST(suite, TestCuStringInit);
    SUITE_ADD_TEST(suite, TestCuStringCStr);
	SUITE_ADD_TEST(suite, TestCuStringConvertCStr);
	SUITE_ADD_TEST(suite, TestCuStringLen);
	SUITE_ADD_TEST(suite, TestCuStringSize);
	SUITE_ADD_TEST(suite, TestCuStringClear);



	return suite;
}

CuSuite* CuStringGetSuite2(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestCuStringAppend);
	SUITE_ADD_TEST(suite, TestCuStringAppendNULL);
	SUITE_ADD_TEST(suite, TestCuStringAppendChar);
	SUITE_ADD_TEST(suite, TestCuStringInserts);
	SUITE_ADD_TEST(suite, TestCuStringResizes);
	SUITE_ADD_TEST(suite, TestCuStringAppendFormat);

	SUITE_ADD_TEST(suite, TestCuStringAppendLineFile);
//	SUITE_ADD_TEST(suite, TestCuStringComposeMessage);
	SUITE_ADD_TEST(suite, TestCuStringAppendULong);



    SUITE_ADD_TEST(suite, TestCuStringAppendISvsNOT);
    SUITE_ADD_TEST(suite, TestCuStringAppendVariadicFormat);
	//alle OK
    return suite;
}
