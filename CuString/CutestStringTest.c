#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CutestString_internal.h"
#include "CuTest_internal.h"
//static void X_CompareAsserts(CuTest* tc, const char *file, int line, const char* message, const char* expected, const char* actual);
#define CompareAsserts(tc, message, expected, actual)  X_CompareAsserts((tc), __FILE__, __LINE__, (message), (expected), (actual))

#define VALUEANDSTRING(type, name, val) type name = (val); char* name##Str = SAVECUSTRINGIFY(val)

char thisfile[] = __FILE__;

/*
static void X_CompareAsserts(CuTest* tc, const char *file, int line, const char* message, const char* expected, const char* actual)
{
	int mismatch;
	if (expected == NULL || actual == NULL) {
		mismatch = (expected != NULL || actual != NULL);
	} else {
		char front[sizeof(__FILE__)+1] = __FILE__;//seems to work now

		const CuSize_t frontLen = sizeof(__FILE__);//strlen(front);
		const CuSize_t expectedLen = strlen(expected);

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
}*/

/*-------------------------------------------------------------------------*
 * CuString Test
 *-------------------------------------------------------------------------*/

void TestCuStringNew(CuTest_t* tc)
{
    // @todo (mc78#1#01/19/18): str->buffer is messed up, after CuString new. Something wents wrong with allocation.
	CuString* str = CuStringNew();
	bool result;
    CuSize_t bufferSize;

	result = CuAlloc_getBufferValidity(str);
	CuAssertTrue(tc, result);
	bufferSize = CuAlloc_getDataSize(str);
	CuAssertTrue(tc, sizeof(CuString) == bufferSize);
	CuAssertTrue(tc, 0 == str->length);

	// @todo (mc78#1#01/19/18): This line crashes when compiled with gcc. Find origin and fix.
	//Cannot determine size of allocated space for str->buffer, because str->buffer is char*
	bufferSize = CuAlloc_getDataSize(str->buffer);
	CuAssertTrue(tc, CUSTRING_LEN_NEW+1 == bufferSize);
	CuAssertTrue(tc, CUSTRING_LEN_NEW+1 == str->size);
	CuAssertStrEquals(tc, "", str->buffer);
	CuStringDelete(str);
}

void TestCuStringDelete(CuTest_t* tc)
{
	CuString* str = CuStringNew();

	CuAssertTrue(tc, CuStringDelete(str));
}

void TestCuStringInit(CuTest_t* tc)
{
	CuString* str = CuStringNew();
	CuStringAppend(str, "this string is more than sixtifour letters long, which is now true!");
    CuFree(str->buffer);
    CuStringInit(str);

	CuAssertTrue(tc, 0 == str->length);
	CuAssertTrue(tc, CUSTRING_LEN_NEW+1 == CuAlloc_getDataSize(str->buffer));
	CuAssertTrue(tc, CUSTRING_LEN_NEW+1 == str->size);
	CuAssertStrEquals(tc, "", str->buffer);
	CuStringDelete(str);
}

void TestCuStringAppend(CuTest_t* tc)
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


void TestCuStringAppendNULL(CuTest_t* tc)
{
	CuString* str = CuStringNew();
	CuStringAppend(str, NULL);
	CuAssertIntEquals(tc, 4, str->length);
	CuAssertStrEquals(tc, "NULL", str->buffer);
	CuStringDelete(str);
}


void TestCuStringAppendChar(CuTest_t* tc)
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


void TestCuStringInserts(CuTest_t* tc)
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


void TestCuStringResizes(CuTest_t* tc)
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

void TestCuStrCopy(CuTest_t* tc)
{
	const char* old = "hello world";
	char* newStr = CuStrCopy(old);
	CuAssertTrue(tc, strcmp(old, newStr) == 0);
	CuFree(newStr);
}


void TestCuStrAlloc(CuTest_t* tc)
{
    CuStringSize_t size = 10;
	char* ptr = CuStrAlloc(size);
	CuAssertTrue(tc, CuAlloc_getBufferValidity(ptr));
	CuAssertIntEquals(tc, CuAlloc_getDataSize(ptr), size+1);
    CuFree(ptr);
}

/* CuSize_t helper_TestCuStrLenVaFormat(char* format, ...){
	va_list va;
	va_start(va, format);

	return CuStrLenVaFormat(format, va);
}
*/

/*
void TestCuStrLenVaFormat(CuTest* tc){
	int num = 10;
	char* subStr = "subStr";
	int len = helper_TestCuStrLenVaFormat("abc %s %d", subStr, num);
	printf("len: %d\n", len);
	CuAssertTrue(tc, len == 13);
}

void TestCuStrLenFormat(CuTest* tc){
	int num = 10;
	char* subStr = "subStr";
	int len = CuStrLenFormat("abc %s %d", subStr, num);
	printf("len: %d\n", len);
	CuAssertTrue(tc, len == 13);
}
*/

void TestCuStrFormat(CuTest_t* tc){
    static char subStr[] = "subStr";
    int num = 10;
	char *str = CuStrFormat("abc %s %d", subStr, num);
	CuAssertTrue(tc, CuAlloc_getBufferValidity(str));
    CuAssertStrEquals(tc, "abc subStr 10", str);
    CuFree(str);
}

char* helper_TestCuStrVaFormat(char* format, ...){
	va_list va;
	va_start(va, format);

	return CuStrVaFormat(format, va);
}

void TestCuStrVaFormat(CuTest_t* tc){
	VALUEANDSTRING(int, val, 10);
	char* buf = helper_TestCuStrVaFormat("g = %d", val);
	if (CuAssertIntEquals(tc, 0, buf[sizeof(valStr)-1])){
		CuAssertTrue(tc, 6 == strlen(buf));
		CuAssertTrue(tc, 0 == strcmp(buf, "g = 10"));
	}
	CuFree(buf);
}

void TestCuStringAppendFormat(CuTest_t* tc)
{
	CuString* str = CuStringNew();
	CuStringAppendFormat(str, "%s,%d,%c", "abc",10,'y');

	/* buffer limit raised to HUGE_STRING_LEN so no overflow */

	CuAssertIntEquals(tc, 8, CuStringLen(str));
	CuAssertStrEquals(tc, "abc,10,y", CuStringCStr(str));
	CuStringDelete(str);
}

// TODO (MyAcer#1#): strEquals functions belong in CuTest not CuString
/*void TestAssertStrEquals(CuTest* tc)
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
*/
void TestCuStringLen(CuTest_t *tc){
	char *teststr = "My test string";
	CuString *str = CuStringConvertCStr(teststr);

	CuAssertIntEquals( tc, CuStringLen(str), strlen(teststr) );
	CuStringDelete(str);
}

// TODO (Stefan#1#): Implement test case!
void TestCuStringClear(CuTest_t* tc){
    CuFail_Msg(tc, "not implemented");
}

void TestCuStrNULL(CuTest_t* tc){
	const char *nullstr = NULL;
	const char *teststr = "a test";

	nullstr = CuStrNULL(nullstr);
	CuAssertIntEquals(tc, 0, strcmp(nullstr,"NULL"));
    CuFree((void*)nullstr);
	nullstr = CuStrNULL(teststr);
	CuAssertStrEquals(tc, nullstr, teststr);

}

void TestCuStringSize(CuTest_t *tc){
	char teststr[] = "Another test string";
	CuString *str = CuStringConvertCStr(teststr);
	CuStringResize(str, sizeof(teststr));
	CuAssertIntEquals( tc, CuStringSize(str), sizeof(teststr) );
	CuStringDelete(str);
}

void TestCuStringResize(CuTest_t *tc){
	char teststr1[] = "a short string";
	char teststr2[] = "a very much longer string";
	CuString *str1 = CuStringConvertCStr(teststr1);
	CuAssertIntEquals( tc, CuStringLen(str1), strlen(teststr1) );
	CuStringResize(str1, sizeof(teststr2));
	CuAssertIntEquals( tc, CuStringSize(str1), sizeof(teststr2) );
	CuAssertIntEquals( tc, CuStringLen(str1), strlen(teststr1) );

	CuStringDelete(str1);

	str1 = CuStringConvertCStr(teststr2);
	CuStringResize(str1, sizeof(teststr1));
	CuAssertIntEquals( tc, CuStringSize(str1), sizeof(teststr1) );
	CuAssertIntEquals( tc, CuStringLen(str1), strlen(teststr1) );

	/*CuStringResize(str1, sizeof(teststr1)/2);
	CuAssertIntEquals( tc, CuStringSize(str1), sizeof(teststr1)/2 );
	CuAssertIntEquals( tc, CuStringLen(str1), sizeof(teststr1)/2-1 );*/
	CuStringDelete(str1);
}

void TestCuStringCStr(CuTest_t *tc){
	CuString *str = CuStringNew();
	const char *desiredStr = "This is a test.";
	//CuStringInit(&str);
	CuStringAppend(str, desiredStr);
	/*CuAssertStrEquals(tc,
					(const char*)CuStringCStr(str),
					(const char*)desiredStr);*/
	CuAssertTrue(tc, 0 == strcmp(CuStringCStr(str), desiredStr));
					//check string content
	//CuAssertIntEquals( tc, strlen(desiredStr), str->length );//check length of string up to \0
	CuAssertTrue(tc, strlen(desiredStr) == str->length );
	//CuAssertIntEquals( tc, CUSTRING_LEN_NEW, str->size );//check occupied memory
	CuAssertTrue(tc, CUSTRING_LEN_NEW+1 == str->size );
	CuStringDelete(str);
}

void TestCuStringAppendLineFile(CuTest_t *tc){
	char frontStr[] = "This file is: ";
	unsigned long line = __LINE__;
    CuString* thisline = CuStringNew();
    char *expected;
	CuString *str = CuStringConvertCStr(frontStr);
	CuStringAppendFormat(thisline, "%lu", line);
	expected = malloc(sizeof(frontStr)+sizeof(thisfile)+strlen(CuStringCStr(thisline))+2+1);
	CuStringAppendLineFile(str, thisfile, line);
	strcpy(expected, frontStr);
	strcat(expected, thisfile);
	strcat(expected, " (");
	strcat(expected, CuStringCStr(thisline));
	strcat(expected, ")");

	CuAssertStrEquals(tc, expected, CuStringCStr(str));
	free(expected);
	CuStringDelete(str);
	CuStringDelete(thisline);
}

void TestCuStringAppendISvsNOT(CuTest_t *tc){
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
void TestCuStringAppendULong(CuTest_t *tc){
	unsigned long int num = 123456;
	char* numStr = "123456";

	CuString *str = CuStringNew();
	CuStringAppendULong(str, num);
	CuAssertStrEquals(tc, numStr, CuStringCStr(str));
	CuStringDelete(str);
}

void TestCuStringConvertCStr(CuTest_t *tc){
	char* testtext = "This is my testtext.";
	CuString *str = CuStringConvertCStr(testtext);
	/*CuAssertStrEquals(tc, testtext, CuStringCStr(str));
	CuAssertIntEquals(tc, CuStringLen(str), strlen(testtext));
	CuAssertIntEquals(tc, CuStringSize(str), CUSTRING_LEN_NEW);*/

	CuAssertTrue(tc, 0 == strcmp(testtext, CuStringCStr(str)));
	CuAssertTrue(tc, CuStringLen(str)== strlen(testtext));
	CuAssertTrue(tc, CuStringSize(str)== CUSTRING_LEN_NEW+1);

	testtext = NULL;
	CuStringDelete(str);

	str = CuStringConvertCStr(testtext);
	//CuAssertStrEquals(tc, "NULL", CuStringCStr(str));
	CuAssertTrue(tc, 0 == strcmp("NULL", CuStringCStr(str)));
	CuStringDelete(str);
}

bool helper_TestCuStringAppendVariadicFormat(CuString *str, char* format, ...){
    va_list va;

    va_start(va, format);
    CuStringAppendVariadicFormat(str, format, va);
    va_end(va);
    return false;
}

void TestCuStringAppendVariadicFormat(CuTest_t *tc){
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

CuSuite_t* CuStringGetSuite1(void)
{
	CuSuite_t* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestCuStrAlloc);
    SUITE_ADD_TEST(suite, TestCuStrCopy);
    SUITE_ADD_TEST(suite, TestCuStrNULL);
    SUITE_ADD_TEST(suite, TestCuStringNew);
    SUITE_ADD_TEST(suite, TestCuStringDelete);
    SUITE_ADD_TEST(suite, TestCuStringResize);
    SUITE_ADD_TEST(suite, TestCuStringInit);
    SUITE_ADD_TEST(suite, TestCuStringCStr);
	SUITE_ADD_TEST(suite, TestCuStringConvertCStr);
	SUITE_ADD_TEST(suite, TestCuStringLen);
	SUITE_ADD_TEST(suite, TestCuStringSize);
	SUITE_ADD_TEST(suite, TestCuStringClear);
//	SUITE_ADD_TEST(suite, TestCuStrLenVaFormat);
	SUITE_ADD_TEST(suite, TestCuStrVaFormat);


	return suite;
}

CuSuite_t* CuStringGetSuite2(void)
{
    CuSuite_t* suite = CuSuiteNew();


	//SUITE_ADD_TEST(suite, TestCuStrLenFormat);
	/*SUITE_ADD_TEST(suite, TestCuStrFormat);
	SUITE_ADD_TEST(suite, TestCuStringInserts);
	SUITE_ADD_TEST(suite, TestCuStringResizes);
	SUITE_ADD_TEST(suite, TestCuStringAppendVariadicFormat);
*/
 	//alle OK
    return suite;
}

CuSuite_t* CuStringGetSuite3(void)
{
    CuSuite_t* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestCuStringAppend);
	SUITE_ADD_TEST(suite, TestCuStringAppendNULL);
	SUITE_ADD_TEST(suite, TestCuStringAppendChar);
	SUITE_ADD_TEST(suite, TestCuStringAppendFormat);
	SUITE_ADD_TEST(suite, TestCuStringAppendLineFile);
	//SUITE_ADD_TEST(suite, TestCuStringComposeMessage);
	SUITE_ADD_TEST(suite, TestCuStringAppendULong);
   SUITE_ADD_TEST(suite, TestCuStringAppendISvsNOT);

	//alle OK
    return suite;
}
