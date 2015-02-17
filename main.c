#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CuTest_internal.h"

int RunAllTests(void);

int main(void)
{
    int NoFails = 1;
	printf("CuTest V1.5 running...\n");
    assert(0 == CuAlloc_getPendingFrees());
	NoFails = RunAllTests();
	printf("Pending frees:%lu", CuAlloc_getPendingFrees());
	//assert(0 == CuAlloc_getPendingFrees());
	return NoFails;
}
