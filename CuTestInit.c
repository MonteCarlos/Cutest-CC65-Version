#include "CuTest_internal.h"

void CuTestInit(CuTest* t, const char* name, TestFunction function)
{
	t->name = CuStrCopy(name);
	t->failed = 0;
	t->ran = 0;
	t->message = CuStringNew();
	t->function = function;
	t->jumpBuf = NULL;
}
