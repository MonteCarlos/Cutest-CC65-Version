#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTest_internal.h"

int RunAllTests(CuSuite_t* suite, FILE* file);
CuSuite_t* CuGetAssertTests(void);
CuSuite_t* CuGetOtherTests(void);
CuSuite_t* CuGetSuiteTests(void);

int main(void)
{
	CuSize_t NoFails = 1;
	printf("CuTest V1.5 running...\n");
    assert(0 == CuAlloc_getPendingFrees());
	NoFails = RunAllTests(CuGetSuiteTests(), stdout);
	NoFails += RunAllTests(CuGetAssertTests(), stdout);
	NoFails += RunAllTests(CuGetOtherTests(), stdout);
	printf("Pending frees:%u", CuAlloc_getPendingFrees());
	//assert(0 == CuAlloc_getPendingFrees());
	return NoFails;
}
