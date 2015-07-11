#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

int CuStringAppendISvsNOT(CuString *str, const char* format,...){
    va_list va;
    char *tempstr = CuStrFormat("is \"%s\" not \"%s\"", format, format);

	va_start(va,format);
  	CuStringAppendVariadicFormat(str, tempstr, va);

    va_end(va);
    CuFree (tempstr);

    return EXIT_SUCCESS;
}
