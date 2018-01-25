#ifndef CUTESTSTRING_INTERNAL_H_INCLUDED
#define CUTESTSTRING_INTERNAL_H_INCLUDED

#include "CutestString.h"
#include "../CuAlloc/CuAlloc.h"
#include <MCLib.h>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
//#include <setjmp.h>

#include "CutestString.h"

/// The struct holding metadata for CuStrings
struct CuString_tag {
    CuStringLen_t length;
    CuStringSize_t size;
    CuStringChar_t *buffer;
} ;

/// If str param is not NULL is is simply passed through, if it is NULL the string "NULL" is assigned
char *CuStrNULL (const char *str);

/// Generates a format string for IS versus NOT comparisons by appending text1, format, text2, format
char *CuStringFormatGenerator(char *text1, char *text2, const char *format);

/// Generates a template format string for formatting of IS vs NOT comparison
char* CuStrFormatISvsNOTTemplate(const char *format);
#endif // CUTESTSTRING_INTERNAL_H_INCLUDED
