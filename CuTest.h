#ifndef CU_TEST_H
#define CU_TEST_H

#include <stdarg.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdheaders.h>

#define CUTEST_VERSION  "CuTest 1.5"

typedef int CuSize_t;
typedef uint8_t CuError_t;

#include "CuString/CutestString.h"
#include "CuAlloc/CuAlloc.h"
/* CuTest */

typedef struct CuSuite_tag CuSuite;
typedef struct CuTest_tag CuTest;
typedef struct CuReport_tag CuReport_t;
typedef CuSuite* CuSuitePtr;
typedef CuTest* CuTestPtr;


typedef int CuTest_SetupFnc_t (void *args);
typedef int CuTest_TeardownFnc_t (void *args);

typedef void (*TestFunction)(CuTest *);
//typedef of a pair of a testname string and a pointer to a test function
typedef struct TestfunctionNamePair_tag{
	char *testname;
	TestFunction fnc;
}TestfunctionNamePair_t;

typedef bool CuTestCmpFnc_t(const void* a, const void *b, char *exp, char *act, size_t maxStrLen, CuString *message);
typedef CuTestCmpFnc_t *CuTestCmpFncPtr_t;

void CuTestInit(CuTest* t, const char* name, TestFunction function);
CuTest* CuTestNew(const char* name, TestFunction function);
bool CuTestRun(CuTest* tc);
bool CuTestDelete(CuTest *t);

int CuRegisterTests(CuSuite *suite, TestfunctionNamePair_t (*testlist)[], CuSize_t n);

/* Internal versions of assert functions -- use the public versions */
void CuFail_Line(CuTest* tc, const char* file, unsigned long int line, const char* message2, const char* message);
bool CuAssert_Line(CuTest* tc, const char* file, unsigned long int line, const char* message, int condition);
bool CuAssertStrEquals_LineMsg(CuTest* tc,
	const char* file, unsigned long int line, const char* message,
	const char* expected, const char* actual);
bool CuAssertIntEquals_LineMsg(CuTest* tc,
	const char* file, unsigned long int line, const char* message,
	int expected, int actual);
/*void CuAssertDblEquals_LineMsg(CuTest* tc,
	const char* file, int line, const char* message,
	double expected, double actual, double delta);*/
bool CuAssertPtrEquals_LineMsg(CuTest* tc,
	const char* file, unsigned long int line, const char* message,
	const void* expected, const void* actual);
bool CuAssertArrayEquals_LineMsg(CuTest* tc, const char* file, unsigned long int line, const char* message,
	const void* expected, const void* actual, CuSize_t elementsize, CuSize_t len);
bool CuAssertArrayEqualsStepFunc_LineMsg(CuTest* tc, const char* file, unsigned long int line, const char* message,
	bool (*stepfunc)(size_t index, void* expected), const void* actual, CuSize_t elementsize, CuSize_t len);
bool CuAssertArrayElementsConstant_LineMsg(CuTest* tc, const char* file, unsigned long int line, const char* message,
	const void* expected, const void* actual, CuSize_t elementsize, CuSize_t len);
bool CuAssertGeneralEquals_LineMsg(CuTest* tc, const char* file, unsigned long int line, const char* message,
	const void *expected, const void *actual, char *expStr, char *actStr, size_t maxStrLen, CuTestCmpFncPtr_t cmpFnc);
/* public assert functions */


#define CuPass(tc)                            CuAssertTrue(tc, true);
#define CuFail(tc)                            CuFail_Line(  (tc), __FILE__, __LINE__, NULL, NULL)
#define CuFail_Msg(tc, ms)                    CuFail_Line(  (tc), __FILE__, __LINE__, (ms), NULL)
#define CuAssert(tc, ms, cond)                CuAssert_Line((tc), __FILE__, __LINE__, (ms), (cond))
#define CuAssertTrue(tc, cond)                CuAssert_Line((tc), __FILE__, __LINE__, "assert failed", (cond))
#define CuAssertFalse(tc, cond)               CuAssert_Line((tc), __FILE__, __LINE__, "assert failed", !(cond))
#define CuAssertTrue_Msg(tc, ms, cond)            CuAssert_Line((tc), __FILE__, __LINE__, (ms), (cond))
#define CuAssertFalse_Msg(tc, ms, cond)           CuAssert_Line((tc), __FILE__, __LINE__, (ms), !(cond))

#define CuAssertStrEquals(tc,ex,ac)           CuAssertStrEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac))
#define CuAssertStrEquals_Msg(tc,ms,ex,ac)    CuAssertStrEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertIntEquals(tc,ex,ac)           CuAssertIntEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac))
#define CuAssertIntEquals_Msg(tc,ms,ex,ac)    CuAssertIntEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertDblEquals(tc,ex,ac,dl)        CuAssertDblEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac),(dl))
#define CuAssertDblEquals_Msg(tc,ms,ex,ac,dl) CuAssertDblEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac),(dl))
#define CuAssertPtrEquals(tc,ex,ac)           CuAssertPtrEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac))
#define CuAssertPtrEquals_Msg(tc,ms,ex,ac)    CuAssertPtrEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertArrayEquals(tc,ex,ac,elemsize,len)           CuAssertArrayEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac),elemsize,len)
#define CuAssertArrayEquals_Msg(tc,ms,ex,ac,elemsize,len)    CuAssertArrayEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac),elemsize,len)
#define CuAssertArrayEqualsStepFunc(tc,func,ac,elemsize,len)           CuAssertArrayEqualsStepFunc_LineMsg((tc),__FILE__,__LINE__,#ac,(func),(ac),elemsize,len)
#define CuAssertArrayEqualsStepFunc_Msg(tc,ms,func,ac,elemsize,len)    CuAssertArrayEqualsStepFunc_LineMsg((tc),__FILE__,__LINE__,(ms),(func),(ac),elemsize,len)
#define CuAssertArrayElementsConstant(tc,ex,ac,elemsize,len)           CuAssertArrayElementsConstant_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac),elemsize,len)
#define CuAssertArrayElementsConstant_Msg(tc,ms,ex,ac,elemsize,len)    CuAssertArrayElementsConstant_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac),elemsize,len)

#define CuAssertPtrNotNull(tc,p)        CuAssert_Line((tc),__FILE__,__LINE__,"null pointer unexpected",((p) != NULL))
#define CuAssertPtrNotNullMsg(tc,msg,p) CuAssert_Line((tc),__FILE__,__LINE__,(msg),((p) != NULL))
#define CuAssertPtrNull(tc,p)        CuAssert_Line((tc),__FILE__,__LINE__,"null pointer expected",((p) == NULL))
#define CuAssertPtrNullMsg(tc,msg,p) CuAssert_Line((tc),__FILE__,__LINE__,(msg),((p) == NULL))

#define CUSUITE_OPEN(suite) CuSuite* suite = CuSuiteNew()
#define CUSUITE_CLOSE(suite) CuSuiteDelete(suite)

#define ID(x) x
#define CUEVAL(x) (x)
#define CUCONCAT(a,b) a##b
#define CUTEST(func) void CUCONCAT(test_,func)(CuTest *tc)
#define TESTNAME(func) CUCONCAT(test_,func)

/* CuSuite */

#define CUTEST_LIST_STORAGERESERVE	20
#define CUSUITE_LIST_STORAGERESERVE	10

#define SUITE_ADD_TEST(SUITE,TEST)	CuSuiteAdd(SUITE, CuTestNew(SAVECUSTRINGIFY(TEST), TEST))
#define SUITE_ADD_SUITE(SUITE1, SUITE2) do{CuSuite* SUITE2 = CuSuiteNew();CuSuiteAddSuite(SUITE1, SUITE2);}while(false)
#define CUTEST_ADD(SUITE,TEST) CuSuiteAdd(SUITE, CuTestNew(SAVECUSTRINGIFY(TESTNAME(TEST)), TESTNAME(TEST)))

void CuSuiteInit(CuSuite* testSuite);
CuSuite* CuSuiteNew(void);
bool CuSuiteDelete(CuSuite *testSuite);
bool CuSuiteAdd(CuSuite* testSuite, CuTest *testCase);
void CuSuiteAddSuite(CuSuite* testSuite, CuSuite* testSuite2); CuSize_t  CuSuiteRun(CuSuite* testSuite);
void CuSuiteSummary(CuSuite* testSuite, FILE* file);
//void CuSuiteDetails(CuSuite* testSuite, CuString* details);
bool CuSuiteDetails(CuSuite* testSuite, FILE* file);

int CuTestSetProgressStartEnd(unsigned long int st, unsigned long int en);
int CuTestPrintProgressState(unsigned long int current, unsigned long int interleave);
void CuTestReservePrintPositions(void);
int CuTestAppendMessage(CuTest *tc, const char* format, ...); CuSize_t CuSuiteGetFailcount(CuSuite* testSuite); CuSize_t CuSuiteGetTestcount(CuSuite* testSuite);
CuReport_t *CuReportNew(void);
bool CuReportDestroy(CuReport_t *rep);
int CuTestFormatReportString(CuString *str, CuSize_t runs, CuSize_t passes, CuSize_t fails, CuSize_t leaks);
CuError_t
CuTest_SuiteInitRunReport(CuError_t (*initSuite)(CuSuite *suite), FILE *file);

#endif /* CU_TEST_H */
