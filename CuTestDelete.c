#include "CuTest_internal.h"

void CuTestDelete(CuTest *t)
{
    bool freeresult;
	if (!t) return;
	if (NULL != t->message){
        CuStringDelete(t->message);
	}
	assert (NULL != t->name);
	CuStringDelete(t->name);
	//assert(freeresult);
	//CuStringDelete(t->name);
	//CuStringDelete(t->name);
	assert (NULL != t);
	freeresult = CuFree(t);
	assert(freeresult);
}
