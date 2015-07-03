#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"


char* CuStrAlloc(CuStringSize_t size)
{
	char* newStr = (char*) CuAlloc ( sizeof(char) * (size) );
	assert (NULL != newStr);
	return newStr;
}
