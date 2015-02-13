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

struct CuTest_tag
{
	CuString *name;
	TestFunction function;
	bool failed;
	bool ran;
	bool reported;
	CuString *message;
	jmp_buf *jumpBuf;
};

struct CuSuite_tag
{
	size_t count;
	CuTest** list;
	size_t failCount;

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



#endif // CUTEST_INTERNAL_H_INCLUDED
