#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppendULong(CuString *str, unsigned long int num){
	char *numStr;
	numStr = CuAlloc( snprintf(NULL, 0, "%lu", num) );
	sprintf(numStr, "%lu", num);
	CuStringAppend(str, numStr);
	CuFree(numStr);
}

