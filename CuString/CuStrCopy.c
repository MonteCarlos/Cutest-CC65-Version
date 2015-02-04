#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

char* CuStrCopy(const char* old)
{
	int len = strlen(old);
	char* newStr = CuAlloc(len+1);//CuStrAlloc(len + 1);
	strcpy(newStr, old);
	return newStr;
}
