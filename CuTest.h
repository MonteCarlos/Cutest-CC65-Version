#ifndef CU_TEST_H
#define CU_TEST_H

#include <stdarg.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>

#define CUTEST_VERSION  "CuTest 1.5"

#include "CuString\CutestString.h"

/* CuTest */

typedef struct CuSuite_tag CuSuite;
typedef struct CuTest_tag CuTest;

typedef void (*TestFunction)(CuTest *);

void CuTestInit(CuTest* t, const char* name, TestFunction function);
CuTest* CuTestNew(const char* name, TestFunction function);
void CuTestRun(CuTest* tc);
void CuTestDelete(CuTest *t);

/* Internal versions of assert functions -- use the public versions */
void CuFail_Line(CuTest* tc, const char* file, int line, const char* message2, const char* message);
bool CuAssert_Line(CuTest* tc, const char* file, int line, const char* message, int condition);
bool CuAssertStrEquals_LineMsg(CuTest* tc,
	const char* file, int line, const char* message,
	const char* expected, const char* actual);
bool CuAssertIntEquals_LineMsg(CuTest* tc,
	const char* file, int line, const char* message,
	int expected, int actual);
/*void CuAssertDblEquals_LineMsg(CuTest* tc,
	const char* file, int line, const char* message,
	double expected, double actual, double delta);*/
bool CuAssertPtrEquals_LineMsg(CuTest* tc,
	const char* file, int line, const char* message,
	void* expected, void* actual);

/* public assert functions */


#define CuFail(tc)                            CuFail_Line(  (tc), __FILE__, __LINE__, NULL, NULL)
#define CuFail_Msg(tc, ms)                    CuFail_Line(  (tc), __FILE__, __LINE__, NULL, (ms))
#define CuAssert(tc, ms, cond)                CuAssert_Line((tc), __FILE__, __LINE__, (ms), (cond))
#define CuAssertTrue(tc, cond)                CuAssert_Line((tc), __FILE__, __LINE__, "assert failed", (cond))

#define CuAssertStrEquals(tc,ex,ac)           CuAssertStrEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac))
#define CuAssertStrEquals_Msg(tc,ms,ex,ac)    CuAssertStrEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertIntEquals(tc,ex,ac)           CuAssertIntEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac))
#define CuAssertIntEquals_Msg(tc,ms,ex,ac)    CuAssertIntEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))
#define CuAssertDblEquals(tc,ex,ac,dl)        CuAssertDblEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac),(dl))
#define CuAssertDblEquals_Msg(tc,ms,ex,ac,dl) CuAssertDblEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac),(dl))
#define CuAssertPtrEquals(tc,ex,ac)           CuAssertPtrEquals_LineMsg((tc),__FILE__,__LINE__,#ac,(ex),(ac))
#define CuAssertPtrEquals_Msg(tc,ms,ex,ac)    CuAssertPtrEquals_LineMsg((tc),__FILE__,__LINE__,(ms),(ex),(ac))

#define CuAssertPtrNotNull(tc,p)        CuAssert_Line((tc),__FILE__,__LINE__,"null pointer unexpected",((p) != NULL))
#define CuAssertPtrNotNullMsg(tc,msg,p) CuAssert_Line((tc),__FILE__,__LINE__,(msg),((p) != NULL))

/* CuSuite */

#define MAX_TEST_CASES	100

#define SUITE_ADD_TEST(SUITE,TEST)	CuSuiteAdd(SUITE, CuTestNew(#TEST, TEST))




void CuSuiteInit(CuSuite* testSuite);
CuSuite* CuSuiteNew(void);
void CuSuiteDelete(CuSuite *testSuite);
void CuSuiteAdd(CuSuite* testSuite, CuTest *testCase);
void CuSuiteAddSuite(CuSuite* testSuite, CuSuite* testSuite2);
void CuSuiteRun(CuSuite* testSuite);
void CuSuiteSummary(CuSuite* testSuite,
					CuString* summary);
//void CuSuiteDetails(CuSuite* testSuite, CuString* details);
void CuSuiteDetails(CuSuite* testSuite /*CuString* details*/, FILE* file);


int CuTestSetProgressStartEnd(unsigned long int st, unsigned long int en);
int CuTestPrintProgressState(unsigned long int current, unsigned long int interleave);
void CuTestReservePrintPositions(void);
int CuTestAppendMessage(CuTest *tc, const char* format, ...);
#endif /* CU_TEST_H */
