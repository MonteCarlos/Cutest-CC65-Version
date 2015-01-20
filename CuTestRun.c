#include "CuTest_internal.h"

void CuTestRun(CuTest* tc)
{
	//jmp_buf buf;
	//tc->jumpBuf = &buf;
	//if (setjmp(buf) == 0)
	//{
		(tc->function)(tc);
    tc->ran = 1;


	//}
	//tc->jumpBuf = 0;
}
