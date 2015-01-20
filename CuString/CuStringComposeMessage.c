#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringComposeMessage(CuString* str, const char* msg1, const char* msg2, const char* file, unsigned long int line){
	CuStringClear(str);
	CuStringAppend(str, msg1);
	if (NULL != msg2){
		CuStringAppend(str, ": ");
		CuStringAppend(str, msg2);
	}
	CuStringAppendChar(str, '\n');
	CuStringAppend(str, file);
	CuStringAppendChar(str, '(');
	CuStringAppendULong(str, line);
	CuStringAppendChar(str, ')');

}
