#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTest_internal.h"

int RunAllTests(CuSuite* suite, FILE* file);
CuSuite* CuGetAssertTests(void);
CuSuite* CuGetOtherTests(void);
CuSuite* CuGetSuiteTests(void);

int main(void)
{
    size_t NoFails = 1;
	printf("CuTest V1.5 running...\n");
    assert(0 == CuAlloc_getPendingFrees());
	NoFails = RunAllTests(CuGetSuiteTests(), stdout);
	NoFails += RunAllTests(CuGetAssertTests(), stdout);
	NoFails += RunAllTests(CuGetOtherTests(), stdout);
	printf("Pending frees:%lu", CuAlloc_getPendingFrees());
	//assert(0 == CuAlloc_getPendingFrees());
	return NoFails;
}
