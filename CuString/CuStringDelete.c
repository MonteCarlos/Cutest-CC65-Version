#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

bool CuStringDelete(CuString *str)
{
    bool freeresult;
	freeresult = (str!=NULL);
	assert(NULL != str);
	assert(NULL != str->buffer);
	freeresult &= CuFree(str->buffer);
	assert(true == freeresult);
	freeresult &= CuFree(str);
	assert(true == freeresult);
	return freeresult;
}
