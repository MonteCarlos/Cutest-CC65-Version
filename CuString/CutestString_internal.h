#ifndef CUTESTSTRING_INTERNAL_H_INCLUDED
#define CUTESTSTRING_INTERNAL_H_INCLUDED

#include "CutestString.h"
#include "..\CuAlloc\CuAlloc.h"
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


char* CuStrNULL(const char* const str);
size_t CuStrLenFormat(char* format, ...);

#endif // CUTESTSTRING_INTERNAL_H_INCLUDED
