#ifndef CUALLOC_H_INCLUDED
#define CUALLOC_H_INCLUDED

#define CU_ALLOC(TYPE) ((TYPE*) CuAlloc(sizeof(TYPE)))
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "../CuTest.h"
//#ifdef __CC65__
    typedef void *CuAllocPtr_t;
//#else
 //   typedef uint8_t *CuAllocPtr_t;
//#endif // __CC65__

CuAllocPtr_t CuAlloc(size_t n);
CuAllocPtr_t CuCalloc(size_t n);
CuAllocPtr_t CuRealloc(void* old, CuSize_t n);
CuSize_t CuAlloc_getDataSize( CuAllocPtr_t ptr); CuSize_t CuAlloc_getTotalSize( CuAllocPtr_t ptr);
bool CuAlloc_getBufferValidity( CuAllocPtr_t ptr);
bool CuFree( CuAllocPtr_t ptr);
unsigned long int CuAlloc_getPendingFrees(void);
unsigned long int CuAlloc_getAllocCount(void);
unsigned long int CuAlloc_getFreeCount(void);
unsigned long int CuAlloc_getReallocCount(void);
CuAllocPtr_t CuAllocGetLastFreedMem(uint8_t idx);

// CUALLOC_H_INCLUDED
#endif


