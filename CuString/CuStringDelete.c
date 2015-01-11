#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringDelete(CuString *str)
{
	if (!str) return;
	assert(NULL != str->buffer);
	free(str->buffer);
	assert(NULL != str);
	free(str);
}
