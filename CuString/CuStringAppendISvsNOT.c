#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

int CuStringAppendISvsNOT(CuString *str, char* format,...){
    enum {ISvsNOTBUFLEN = 200};

    va_list va;
    char* tempstr = malloc(ISvsNOTBUFLEN);

    va_start(va,format);
    snprintf(tempstr,ISvsNOTBUFLEN,"IS %s NOT %s",format,format);

    if (!strcmp(format, "%s")){
        CuStringAppendFormat(str, tempstr, va_arg(va, char*), va_arg(va, char*) );
    }else if (!strcmp(format, "%d")){
        CuStringAppendFormat(str, tempstr, va_arg(va, int), va_arg(va, int) );
    }else if (!strcmp(format, "%u")){
        CuStringAppendFormat(str, tempstr, va_arg(va, unsigned int), va_arg(va, unsigned int) );
    }

    va_end(va);
    free (tempstr);

    return EXIT_SUCCESS;
}
