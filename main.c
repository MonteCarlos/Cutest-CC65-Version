#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int RunAllTests(void);

int main(void)
{
    int NoFails = 1;
	printf("CuTest V1.5 running...\n");
    assert(0 == CuAlloc_getPendingFrees());
	NoFails = RunAllTests();
	assert(0 == CuAlloc_getPendingFrees());
	return NoFails;
}
