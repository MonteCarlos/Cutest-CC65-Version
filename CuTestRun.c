#include "CuTest_internal.h"

void CuTestRun(CuTest* tc)
{
	//jmp_buf buf;
	//tc->jumpBuf = &buf;
	//if (setjmp(buf) == 0)
	//{
	(tc->function)(tc);
    tc->ran = 1;
	if (!tc->assertCnt){fputs("no assertions", stdout);}

	//}
	//tc->jumpBuf = 0;
}
