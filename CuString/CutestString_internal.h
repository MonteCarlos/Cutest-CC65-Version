#ifndef CUTESTSTRING_INTERNAL_H_INCLUDED
#define CUTESTSTRING_INTERNAL_H_INCLUDED

#include "CutestString.h"
#include <stdarg.h>
#include <stdint.h>
//#include <setjmp.h>


struct CuString_tag
{
	CuStringLen_t length;
	CuStringSize_t size;
	CuStringChar_t* buffer;
} ;

#endif // CUTESTSTRING_INTERNAL_H_INCLUDED
