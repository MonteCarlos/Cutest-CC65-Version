#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

int CuStringAppendISvsNOT(CuString *str, const char* format,...){
    const uint16_t ISvsNOTBUFLEN = 512;
    va_list va;
    char* tempstr = malloc(ISvsNOTBUFLEN);

    va_start(va,format);
    snprintf(tempstr,ISvsNOTBUFLEN,"IS \"%s\" NOT \"%s\"",format,format);

    if (!strcmp(format, "%s")){
        char *is = va_arg(va, char*), *isnot = va_arg(va, char*);
        CuStringAppendFormat(str, tempstr, is, isnot);
    }else if (!strcmp(format, "%d")){
        int is = va_arg(va, int), isnot = va_arg(va, int);
        CuStringAppendFormat(str, tempstr, is, isnot);
    }else if (!strcmp(format, "%u")){
        unsigned int is = va_arg(va, unsigned int), isnot = va_arg(va, unsigned int);
        CuStringAppendFormat(str, tempstr, is, isnot);
    }

    va_end(va);
    free (tempstr);

    return EXIT_SUCCESS;
}
