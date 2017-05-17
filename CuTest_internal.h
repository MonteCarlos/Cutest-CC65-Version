#ifndef CUTEST_INTERNAL_H_INCLUDED
#define CUTEST_INTERNAL_H_INCLUDED

#include <MCLib.h>
#include <stdheaders.h>

#include "CuString/CutestString_internal.h"
#include "CuTest.h"
#include "CuTestTest.h"
#include "CuAlloc/CuAlloc.h"

#define CUTEST_STR_SUMMARY(runs, passes, fails, leaks) "Runs:%u, Passes:%u, Fails:%u, Leaks:%u\n", runs, passes, fails, leaks

typedef struct CuTest_flags_tag{
	int failed:1;
	int ran:1;
	int reported:1;
	int memoryleak:1;
}CuTest_flags_t;

struct CuTest_tag
{
	CuString *name;
	TestFunction function;
	//CuTest_flags_t; //anonymous struct inside so that failed, ran, reported flags are still valid
	bool failed;
	bool ran;
	bool reported;
	bool memoryleak;


	CuSize_t assertCnt;//counter for assertions used in that test
	CuString *message;
	jmp_buf *jumpBuf;
    CuTest_SetupFnc_t *setup;
    CuTest_TeardownFnc_t *teardown;
    va_list vaargs1;
    va_list vaargs2;
};

typedef struct CuTestPtr_tag{
    union{
        CuTest* test;
        CuSuite* suite;
    };
    bool isSuite;
} CuTestPtr_t;

struct CuSuite_tag
{
	CuSize_t testcount;
	CuSize_t suitecount;
    CuSize_t failCount;
    CuSize_t totalcount;
    bool ran;
	CuString *name;
	CuTestPtr_t *testlist;
	bool isSubSuite;
	CuReport_t *report;
};

struct CuReport_tag{
    CuSize_t reportedTests;
    CuSize_t performedTests;
    CuSize_t reportedFails;
    CuSize_t reportedPasses;
    CuString *reportStr;
};


void CuFailInternal(CuTest* tc, const char* file, unsigned long int line, CuString* string);
void *CuTestAlloc(size_t n);
unsigned long int CuTestGetProgressStart(void);
unsigned long int CuTestGetProgressEnd(void);
unsigned long int CuTestGetProgressRange(void);
CuError_t CuTestGenerateMessage(CuString* str, const char* msg1, const char* msg2, const char* file, unsigned long int line);
size_t CuTestFprintf(FILE* file, char* format, ...);


#endif // CUTEST_INTERNAL_H_INCLUDED
