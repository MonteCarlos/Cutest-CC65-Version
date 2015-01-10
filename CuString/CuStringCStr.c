#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

char* CuStringCStr(CuString* str){
	return str->buffer;
}

