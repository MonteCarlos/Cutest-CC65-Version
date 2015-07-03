#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

char* CuStrCopy(const char* old)
{
	char* newStr = CuAlloc(strlen(old)+1);//CuStrAlloc(len + 1);
	strcpy(newStr, old);
	return newStr;
}
