#include "CuTest_internal.h"

bool CuTestDelete(register CuTest_t *t)
{
    if (t){
		bool freeresult;
		//if (NULL == t) return;
		assert (NULL != t);

		if (NULL != t->message){
			CuStringDelete(t->message);
		}
		assert (NULL != t->name);
		CuStringDelete(t->name);
		//assert(freeresult);
		//CuStringDelete(t->name);
		//CuStringDelete(t->name);
		//assert (NULL != t);
		freeresult = CuFree(t);
		assert(freeresult);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
