#ifndef CUALLOC_H_INCLUDED
#define CUALLOC_H_INCLUDED

#define CUALLOC_VERSION  "CuAlloc V 06_08_10"

#define CU_ALLOC(TYPE) ((TYPE*) CuAlloc(sizeof(TYPE)))
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include "../CuTest.h"

struct CuAllocUserData_tag{
    uint8_t (*array)[];
};


typedef void *CuAllocPtr_t;
typedef CuSize_t CuAllocSize_t;
typedef void *CuAllocUserDataPtr_t;

CuAllocUserDataPtr_t CuAlloc(size_t n);
CuAllocUserDataPtr_t CuCalloc(size_t n);
CuAllocUserDataPtr_t CuRealloc(void *old, CuSize_t n);

/* Alloc Functions separating error and return values */
CuError_t CuAlloc2(size_t n, CuAllocPtr_t **mem);
CuError_t CuCalloc2(size_t n, CuAllocPtr_t **mem);
CuError_t CuRealloc2(CuAllocPtr_t* old, CuAllocPtr_t **new, CuSize_t n);

CuSize_t CuAlloc_getDataSize( CuAllocUserDataPtr_t ptr);
CuSize_t CuAlloc_getTotalSize( CuAllocUserDataPtr_t ptr);
bool CuAlloc_getBufferValidity( CuAllocUserDataPtr_t ptr);
bool CuFree( CuAllocPtr_t ptr);
CuSize_t CuAlloc_getPendingFrees(void);
CuSize_t CuAlloc_getAllocCount(void);
CuSize_t CuAlloc_getFreeCount(void);
CuSize_t CuAlloc_getReallocCount(void);
CuAllocPtr_t CuAllocGetLastFreedMem(uint8_t idx);

// CUALLOC_H_INCLUDED
#endif


