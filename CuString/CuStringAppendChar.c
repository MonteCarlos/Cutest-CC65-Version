#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppendChar(CuString* str, char ch)
{
	char text[2]={};
	if ('\0' != ch){
		text[0] = ch;
		CuStringAppend(str, text);
	}//do not append termination character only
}
