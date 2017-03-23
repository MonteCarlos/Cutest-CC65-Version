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


struct CuString_tag
{
	CuStringLen_t length;
	CuStringSize_t size;
	CuStringChar_t* buffer;
} ;


const char* CuStrNULL(const char* str);
size_t CuStrLenFormat(const char* const format, ...);
size_t CuStrLenVaFormat(const char* const format, va_list va);

#endif // CUTESTSTRING_INTERNAL_H_INCLUDED
