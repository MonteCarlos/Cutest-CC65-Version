#ifndef CU_TEST_H
#define CU_TEST_H

#define CUTEST_VERSION  "CuTest V 07_08_10"

#include <stdheaders.h>

/*
 * -------------
 * Misc typedefs
 * -------------
 */

/**< Typedef own size type so that %u format specifier works */
typedef unsigned int CuSize_t;

/**< Typedef error type for return values of CuTest functions */
typedef int8_t CuError_t;

/* Position these includes after typedefs for CuSize_t and CuError_t
 * as these types are also used in CuString and CuAlloc
 */
#include "CuTest_Typedefs.h"
#include "CuTest_AssertMacros.h"
#include "CuTest_AssertFunctions.h"
#include "CuString/CutestString.h"
#include "CuAlloc/CuAlloc.h"
/*
 * ---------------------------------
 * Useful macros in creating messages for assertions
 * ---------------------------------
 */
#define ID(x) x
#define CUEVAL(x) (x)
#define CUCONCAT(a,b) a##b
#define COMMA ,
#define SEMICOLON ;

/*
 * ---------------------------------
 * Useful macros for quicker set-up of test projects
 * ---------------------------------
 */

//macro to create list elements consisting of a testname string and a pointer to a test function
#define CU_MKTESTNAMEPAIR(test) {SAVECUSTRINGIFY(TESTNAME(test)), TESTNAME(test)}
#define CU_MKTESTPROTOTYPE(x) void TESTNAME(x)(CuTest_t *tc);

#define CU_MKTESTPROTOTYPELIST(tests) tests(CU_MKTESTPROTOTYPE, )

#define CU_TESTNAMEPAIRITEM(x) CU_MKTESTNAMEPAIR(x)
#define CU_MKTESTNAMEPAIRLIST(xmacroname, arrayname) \
    static TestfunctionNamePair_t arrayname[] = {xmacroname(CU_TESTNAMEPAIRITEM, COMMA), { NULL, 0 }};

//#define CU_MKTESTLIST(xmacro, name) CuTestlist_t name = {{xmacroname(CU_TESTNAMEPAIRITEM, COMMA)}};

/*
 * ---------------------------------
 * Prototypes for creation/deletion functions for tests
 * ---------------------------------
 */
/**< Initializes a CuTest_t structure with given params and defaults */
void CuTestInit (CuTest_t *t, const char *name, TestFunction function);
/**< Creates a CuTest_t structure initialized with given name and TestFunction. Calls CuTestInit*/
CuTest_t *CuTestNew (const char *name, TestFunction function);
/**< Deletes a test and deallocates mem */
bool CuTestDelete (CuTest_t *t);
/**< Runs the TestFunction stores in the given CuTest_t structure and logs if it fails */
bool CuTestRun (CuTest_t *tc);

/*
 * ---------------------------------
 * Prototypes for creation/deletion functions for suites
 * ---------------------------------
 */
/**< Initializes a CuSuite_t structure with defaults */
void CuSuiteInit (CuSuite_t *testSuite);
/**< Allocates and creates a new CuSuite_t structure and initializes it with defaults */
CuSuite_t *CuSuiteNew (void);
/**< Deletes and deallocates a CuSuite_t structure */
bool CuSuiteDelete (CuSuite_t *testSuite);

/*
 * ---------------------------------
 * Prototypes for convenience functions
 * ---------------------------------
 */
/**< Given a suite and a list of testnames and corresponding test functions, register all tests of the list */
CuError_t CuSuiteRegisterTests (CuSuite_t *suite, TestfunctionNamePair_t (*testlist) [], CuSize_t n);
/**< Given a suite and a testlist structure consisting of count, testnames and
     corresponding test functions, register all tests of the list */
CuError_t CuSuiteRegisterTestlist(CuSuite_t *suite, CuTestlist_t *testlist);
CuError_t CuSuiteRegisterNULLTerminatedTestlist (CuSuite_t *suite, void *testlist);
CuError_t CuSuiteInitRunReport (CuSuiteInitFnc_t *initSuite, FILE *file, void *params);

/*
 * ---------------------------------
 * Convenience macros
 * ---------------------------------
 */
/**< Convinience macro to create a suite and also a variable with the given name */
#define CUSUITE_OPEN(suite) CuSuite_t* suite = CuSuiteNew()
/**< Convinience macro to delete a suite with the given name */
#define CUSUITE_CLOSE(suite) CuSuiteDelete(suite)

/**< Convinience macro to generate prototype for a test function */
#define CUTEST(func) void CUCONCAT(test_,func)(CuTest_t *tc)
/**< Convinience macro to generate a name for a test function (appends test_ to given name) */
#define TESTNAME(func) CUCONCAT(test_,func)

/* CuSuite */
/**< Adds a new test with given testfunction to given suite */
#define SUITE_ADD_TEST(SUITE,TEST)  CuSuiteAddTest(SUITE, CuTestNew(SAVECUSTRINGIFY(TEST), TEST))
/**< Adds a new test with given testfunction to given suite and prepends "_test" to function names */
#define CUTEST_ADD(SUITE,TEST) CuSuiteAddTest(SUITE, CuTestNew(SAVECUSTRINGIFY(TESTNAME(TEST)), TESTNAME(TEST)))
/**< Adds given suite2 to given suite1 */
#define SUITE_ADD_SUITE(SUITE1, SUITE2) do{CuSuite_t* SUITE2 = CuSuiteNew();CuSuiteAddSuite(SUITE1, SUITE2);}while(false)



bool CuSuiteAddTest (CuSuite_t *testSuite, CuTest_t *testCase);
void CuSuiteAddSuite (CuSuite_t *testSuite, CuSuite_t *testSuite2);
CuSize_t  CuSuiteRun (CuSuite_t *testSuite);
void CuSuiteSummary (CuSuite_t *testSuite, FILE *file);
bool CuSuiteDetails (CuSuite_t *testSuite, FILE *file);
CuSize_t CuSuiteGetFailcount (CuSuite_t *testSuite);
CuSize_t CuSuiteGetTestcount (CuSuite_t *testSuite);

int CuTestAppendMessage (CuTest_t *tc, const char *format, ...);

CuReport_t *CuReportNew (void);
bool CuReportDestroy (CuReport_t *rep);
int CuTestFormatReportString (CuString *str, CuSize_t runs, CuSize_t passes, CuSize_t fails, CuSize_t leaks);

int CuTestSetProgressStartEnd (unsigned long int st, unsigned long int en);
int CuTestPrintProgressState (unsigned long int current, unsigned long int interleave);
void CuTestReservePrintPositions (void);

#endif /* CU_TEST_H */
