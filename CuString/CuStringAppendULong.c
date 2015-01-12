#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppendULong(CuString *str, unsigned long int num){
	char numStr[20];
	sprintf(numStr, "%lu", num);
	CuStringAppend(str, numStr);
}

