#ifndef CUTEST_INTERNAL_H_INCLUDED
#define CUTEST_INTERNAL_H_INCLUDED

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "CuString\CutestString_internal.h"
#include "CuTest.h"
#include "CuTestTest.h"
#include "CuAlloc\CuAlloc.h"

#define CUTEST_STR_SUMMARY(runs, passes, fails, leaks) "Runs:%u, Passes:%u, Fails:%u, Leaks:%u\n", runs, passes, fails, leaks

struct CuTest_tag
{
	CuString *name;
	TestFunction function;
	bool failed;
	bool ran;
	bool reported;
	bool memoryleak;
	CuString *message;
	jmp_buf *jumpBuf;
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
	size_t testcount;

	CuTestPtr_t *testlist;
	size_t failCount;
	CuReport_t *report;
};

struct CuReport_tag{
    size_t reportedTests;
    size_t performedTests;
    size_t reportedFails;
    size_t reportedPasses;
    CuString *reportStr;
};


void CuFailInternal(CuTest* tc, const char* file, int line, CuString* string);
void *CuTestAlloc(size_t n);
unsigned long int CuTestGetProgressStart(void);
unsigned long int CuTestGetProgressEnd(void);
unsigned long int CuTestGetProgressRange(void);
void CuTestGenerateMessage(CuString* str, const char* msg1, const char* msg2, const char* file, unsigned long int line);
size_t CuTestFprintf(FILE* file, char* format, ...);


#endif // CUTEST_INTERNAL_H_INCLUDED
