#include "CuTest_internal.h"

void CuTestInit(register CuTest* t, const char* name, TestFunction function)
{
	t->name = CuStringConvertCStr(name);//CuStrCopy(name);
	t->failed = t->ran = t-> reported = false;
	t->message = CuStringNew();
	t->function = function;
	t->jumpBuf = NULL;
	t->memoryleak = false;
}
