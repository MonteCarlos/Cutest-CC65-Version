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
struct CuString_tag
{
	CuStringLen_t length;
	CuStringSize_t size;
	CuStringChar_t* buffer;
} ;


const char* CuStrNULL(const char* str);CuSize_t CuStrLenFormat(const char* const format, ...);char *CuStrVaFormat(const char* const format, va_list va);
int CuStrGetVAExpandedFormatStringLength(const char *format, va_list va);
CuError_t CuStringAppendISvsNOTStr(CuString *str, const char *expected, const char *actual);

#endif // CUTESTSTRING_INTERNAL_H_INCLUDED
