#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

//Use long for line number to be not limited to 65535 lines per file
void CuStringAppendLineFile(CuString* str, char* file, unsigned long int line){
	CuStringAppendFormat(str,"%s (%lu)", file, line);
}
