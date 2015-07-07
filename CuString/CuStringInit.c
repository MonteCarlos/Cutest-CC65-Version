
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"
void CuStringInit(register CuString* str)
{
	str->length = 0;
	str->size = CUSTRING_LEN_NEW;
	//initializes string to zero, too!
	str->buffer = CuStrAlloc(CUSTRING_LEN_NEW-1);
	assert(str->buffer != NULL);
}
