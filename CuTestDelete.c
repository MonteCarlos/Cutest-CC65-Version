#include "CuTest_internal.h"

void CuTestDelete(CuTest *t)
{
	if (!t) return;
	assert (NULL != t->name);
	free(t->name);
	//CuStringDelete(t->name);
	assert (NULL != t);
	free(t);
}
