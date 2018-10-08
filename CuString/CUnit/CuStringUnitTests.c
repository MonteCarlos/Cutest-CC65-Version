
/*
 *  Simple example of a CUnit unit test.
 *
 *  This program (crudely) demonstrates a very simple "black box"
 *  test of the standard library functions fprintf() and fread().
 *  It uses suite initialization and cleanup functions to open
 *  and close a common temporary file used by the test functions.
 *  The test functions then write to and read from the temporary
 *  file in the course of testing the library functions.
 *
 *  The 2 test functions are added to a single CUnit suite, and
 *  then run using the CUnit Basic interface.  The output of the
 *  program (on CUnit version 2.0-2) is:
 *
 *           CUnit : A Unit testing framework for C.
 *           http://cunit.sourceforge.net/
 *
 *       Suite: Suite_1
 *         Test: test of fprintf() ... passed
 *         Test: test of fread() ... passed
 *
 *       --Run Summary: Type      Total     Ran  Passed  Failed
 *                      suites        1       1     n/a       0
 *                      tests         2       2       2       0
 *                      asserts       5       5       5       0
 */

#include <stdheaders.h>
#include <CuTest.h>
#include <CuString/CutestString_internal.h>
#include <MCLib.h>
#include <minunit.h>

typedef void (*pTestFunction)(void);
//typedef of a pair of a testname string and a pointer to a test function
typedef struct CU_testfunction_name_pair_tag{
	char *testname;
	pTestFunction fnc;
}CU_testfunction_name_pair_t;

//int CU_register_tests(CU_pSuite suite, CU_testfunction_name_pair_t(*testlist)[], size_t n);
#define CU_MAKETESTNAMEPAIR(test) {SAVECUSTRINGIFY(test), test}

/* Some test strings and values
*/

static char testStr[] = "test";
static char thisFile[] = __FILE__;

int inum10 = 10;

/* Function to register several tests at once to CUnit
 * Accepts a testlist and a testcount. Registers all tests in this list up to testcount.
*/
/*
int CU_register_tests(CU_pSuite suite, CU_testfunction_name_pair_t (*testlist)[], size_t n){
	if (suite){
		size_t i;
		CU_testfunction_name_pair_t *thistest = (CU_testfunction_name_pair_t*)testlist;

		for (i=0; i<n; ++i){
			if (!CU_add_test(suite, thistest->testname, thistest->fnc)){
				CU_cleanup_registry();
				return CU_get_error();
			}
			++thistest;
		}
		return CUE_SUCCESS;
	}
	return CUE_NOSUITE;
}
*/

int getZero(void){
	return 0;
}

int getInt(int i){
	static int my_i;
	if (i){
		my_i = i;
	}
	return my_i;
}

char getCh(char c){
	static char my_c;
	if (c){
		my_c = c;
	}
	return my_c;
}

long int getLong(long int l){
	static int my_l;
	if (l){
		my_l = l;
	}
	return my_l;
}

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
    return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    return 0;
}

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
int helper_CuStrGetVAExpandedFormatStringLength(const char *format, ...){
	int result;
	va_list va;
	va_start(va, format);
	result = CuStrGetVAExpandedFormatStringLength(format, va);
	va_end(va);
	return result;
}

char *helper_CuStrVAFormat(const char *format, ...){
	char *result;
	va_list va;
	va_start(va, format);
	result = CuStrVaFormat(format, va);
	assert(NULL != result);
	va_end(va);
	return result;
}

void Test_CuStrGetVAExpandedFormatStringLength_Returns0OnEmptyString(void){
	char emptyString[] = "";
	mu_assert_equal(0,helper_CuStrGetVAExpandedFormatStringLength(emptyString));
	/*CuTest *tc = CuTestNew("test", NULL);
	CuFail_Line(tc, "thisfile.c", 100000, "msg1", "msg2");
    mu_assert_str_eq("blabl", tc->message->buffer);
	*/
}

void Test_CuStrGetVAExpandedFormatStringLength_ReturnsStrLenOnPlainStr(void){
	//don't insert format specifiers here
	char *plainString = "abc";
	mu_assert_equal(strlen(plainString),helper_CuStrGetVAExpandedFormatStringLength(plainString));
	plainString = "abcdefghijklm";
	mu_assert_equal(strlen(plainString),helper_CuStrGetVAExpandedFormatStringLength(plainString));
	plainString = "a";
	mu_assert_equal(strlen(plainString),helper_CuStrGetVAExpandedFormatStringLength(plainString));

}

void Test_CuStrGetVAExpandedFormatStringLength_ReturnsNegOnParseError(void){
	mu_check(helper_CuStrGetVAExpandedFormatStringLength(NULL)<0);
}

void Test_CuStrGetVAExpandedFormatStringLength_ReturnsExpandedStrLenCorrectly(void){
	const char *format = "%d, %u, %c, %s, %ld";
	char *myString = testStr;
	int myint = 100;
	unsigned int myuint = 10000;
	char mych = 'a';
	long int mylong = 100000;
	char chArray[100];

	snprintf(chArray, sizeof(chArray), format, myint, myuint, mych, myString, mylong);
	mu_assert_equal(strlen(chArray), helper_CuStrGetVAExpandedFormatStringLength(format, myint, myuint, mych, myString, mylong));
}

void Test_CuStrVaFormat_ReturnsStringDuplicateGivenNoFormatSpecifiers(void){
	char *dpStr;

	mu_assert_str_eq(testStr, dpStr = helper_CuStrVAFormat(testStr));
	CuFree (dpStr);
}

void Test_CuStrVaFormat_ReturnsExpandedStringGivenFormatSpecifiers(void){
	char *myTestFormatString = "Name: %s, Value: %d";
	char *dpStr;
	char chArray[200];
	snprintf(chArray, sizeof(chArray), myTestFormatString, thisFile, inum10);
	mu_assert_str_eq(chArray, dpStr = helper_CuStrVAFormat(myTestFormatString, thisFile, inum10));

	CuFree (dpStr);
}

MU_TEST(Test_ISvsNOTStr_ReturnsSubstitutedString){
	CuString *str = CuStringNew();
	char *str1 = "a";
	char *str2 = "b";
	char buf[100];

	snprintf(buf, sizeof(buf), "IS \"%s\" not \"%s\"", str1, str2);
	CuStringAppendISvsNOTStr(str, str1, str2);
	mu_assert_str_eq(
	CuStringDelete(str);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */

void ConfirmThatTestsCompleted(void){

}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(Test_CuStrGetVAExpandedFormatStringLength_Returns0OnEmptyString);
	MU_RUN_TEST(Test_CuStrGetVAExpandedFormatStringLength_ReturnsStrLenOnPlainStr);
	MU_RUN_TEST(Test_CuStrGetVAExpandedFormatStringLength_ReturnsNegOnParseError);
	MU_RUN_TEST(Test_CuStrGetVAExpandedFormatStringLength_ReturnsExpandedStrLenCorrectly);
	MU_RUN_TEST(Test_CuStrVaFormat_ReturnsStringDuplicateGivenNoFormatSpecifiers);
	MU_RUN_TEST(Test_CuStrVaFormat_ReturnsExpandedStringGivenFormatSpecifiers);
	MU_RUN_TEST(ConfirmThatTestsCompleted);
}

int main()
{
	/*CU_pSuite pSuite = NULL;
	CU_testfunction_name_pair_t tests[] =
	{
		CU_MAKETESTNAMEPAIR(Test_CuStrGetVAExpandedFormatStringLength_Returns0OnEmptyString),
		CU_MAKETESTNAMEPAIR(Test_CuStrGetVAExpandedFormatStringLength_ReturnsStrLenOnPlainStr),
		CU_MAKETESTNAMEPAIR(Test_CuStrGetVAExpandedFormatStringLength_ReturnsNegOnParseError),
		CU_MAKETESTNAMEPAIR(Test_CuStrGetVAExpandedFormatStringLength_ReturnsExpandedStrLenCorrectly),
		CU_MAKETESTNAMEPAIR(Test_CuStrVaFormat_ReturnsStringDuplicateGivenNoFormatSpecifiers),
		CU_MAKETESTNAMEPAIR(Test_CuStrVaFormat_ReturnsExpandedStringGivenFormatSpecifiers),
		CU_MAKETESTNAMEPAIR(ConfirmThatTestsCompleted)
	};


	// initialize the CUnit test registry
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	// add a suite to the registry
	pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	// add the tests to the suite
	CU_register_tests(pSuite, &tests, ELEMCNT(tests));

	// Run all tests using the CUnit Basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_automated_run_tests();
	CU_basic_run_tests();
	//CU_curses_run_tests();
	CU_cleanup_registry();
	return CU_get_error();*/
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return minunit_fail;
}
