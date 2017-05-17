#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/* Appends unsiged long to a CuString after the number itself is also converted to a string*/

CuError_t CuStringAppendULong(CuString *str, unsigned long int num){
	//CuStringAppendFormat already checks str
		return CuStringAppendFormat(str, "%lu", num);
}

