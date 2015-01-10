#ifndef CUTEST_INTERNAL_H_INCLUDED
#define CUTEST_INTERNAL_H_INCLUDED

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "CuString\CutestString_internal.h"
#include "CuTest.h"
#include "CuTestTest.h"

struct CuTest_tag
{
	char* name;
	TestFunction function;
	int failed;
	int ran;
	const char* message;
	jmp_buf *jumpBuf;
};

struct CuSuite_tag
{
	int count;
	CuTest** list;
	int failCount;

};

static void CuFailInternal(CuTest* tc, const char* file, int line, CuString* string);





#endif // CUTEST_INTERNAL_H_INCLUDED
