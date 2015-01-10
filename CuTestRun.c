#include "CuTest_internal.h"

void CuTestRun(CuTest* tc)
{
	jmp_buf buf;
	tc->jumpBuf = &buf;
	if (setjmp(buf) == 0)
	{
		tc->ran = 1;
		(tc->function)(tc);


	}
	tc->jumpBuf = 0;
}
