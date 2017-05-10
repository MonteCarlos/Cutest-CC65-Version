#ifndef CUALLOC_INTERNAL_H_INCLUDED
#define CUALLOC_INTERNAL_H_INCLUDED

#include "CuAlloc.h"

typedef struct CuAlloc_BufHeader_tag CuAlloc_BufHeader_t;
typedef struct CuAlloc_tag CuAlloc_t;

struct CuAlloc_BufHeader_tag{
    uint8_t dataOffset;
    uint8_t (*data)[];
    CuSize_t datasize;
    CuSize_t totalsize;
    CuAlloc_t *this;
};

struct CuAlloc_tag {
    CuAlloc_BufHeader_t;//Anonymous Struct
    uint8_t array[];//Variable length array
};

extern unsigned long int alloccount;
extern unsigned long int freecount;
extern unsigned long int realloccount;
extern void *lastFreed[5];
extern void *lastAllocated[5];

void CuAlloc_initHeader(CuAlloc_t* ptr, CuSize_t n);
CuAlloc_t *CuAlloc_getHeaderAddr(CuAllocPtr_t ptr);
CuAllocPtr_t CuAlloc_getDataAddr(CuAlloc_t*  ptr); CuSize_t CuAlloc_calculateTotalSize(size_t n);

// CUALLOC_INTERNAL_H_INCLUDED
#endif

