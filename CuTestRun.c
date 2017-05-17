#include "CuTest_internal.h"

bool CuTestRun(CuTest* tc)
{
	if (tc){
		//jmp_buf buf;
		//tc->jumpBuf = &buf;
		//if (setjmp(buf) == 0)
		//{
		if (tc->function){
			(tc->function)(tc);
		}

		if (!tc->assertCnt){fputs("!no assertions!", stdout);}
		tc->ran = 1;

		//}
		//tc->jumpBuf = 0;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
