
#include "CutestString_internal.h"

char *CuStrFormat(char* format, ...){
    va_list argp;
    va_start(argp, format);
	return CuStrVaFormat(format, argp);
}
