#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

CuStringSize_t CuStringSize(CuString *str){
	return str -> size;
}
