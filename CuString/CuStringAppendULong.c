#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppendULong(CuString *str, unsigned long int num){
	CuStringAppendFormat(str, "%lu", num);
}

