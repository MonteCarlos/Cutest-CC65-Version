#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"


char* CuStrAlloc(CuStringSize_t size)
{
    //allocate room for terminating \0 character, too
    //newly allocated string should be valid and empty, thats why we use Calloc instead of just Alloc
	char* newStr = (char*) CuCalloc ( sizeof(char) * (size+1) );
	assert (NULL != newStr);

	return newStr;
}
