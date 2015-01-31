#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void RunAllTests(void);

int main(void)
{
	printf("CuTest V1.5 running...\n");
    assert(0 == CuAlloc_getPendingFrees());
	RunAllTests();
	assert(0 == CuAlloc_getPendingFrees());
	return 0;
}
