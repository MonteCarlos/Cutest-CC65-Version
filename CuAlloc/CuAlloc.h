#ifndef CUALLOC_H_INCLUDED
#define CUALLOC_H_INCLUDED

#define CU_ALLOC(TYPE)		((TYPE*) CuAlloc(sizeof(TYPE)))
#include <stdlib.h>

void *CuAlloc(size_t n);
void *CuCalloc(size_t n);
void *CuRealloc(void* old, size_t n);
size_t CuAlloc_getDataSize(void *ptr);
size_t CuAlloc_getTotalSize(void *ptr);
bool CuAlloc_getBufferValidity(void *ptr);
bool CuFree(void *ptr);
unsigned long int CuAlloc_getPendingFrees(void);
unsigned long int CuAlloc_getAllocCount(void);
unsigned long int CuAlloc_getFreeCount(void);
unsigned long int CuAlloc_getReallocCount(void);

#endif // CUALLOC_H_INCLUDED
