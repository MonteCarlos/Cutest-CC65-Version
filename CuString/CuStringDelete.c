#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringDelete(CuString *str)
{
    bool freeresult;
	if (!str) return;
	assert(NULL != str->buffer);
	freeresult = CuFree(str->buffer);
	assert(true == freeresult);
	assert(NULL != str);
	freeresult = CuFree(str);
	assert(true == freeresult);
}
