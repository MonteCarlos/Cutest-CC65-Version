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

extern CuSize_t alloccount;
extern CuSize_t freecount;
extern CuSize_t realloccount;
extern void *lastFreed[5];
extern void *lastAllocated[5];

CuError_t CuAlloc_initHeader(CuAlloc_t* ptr, CuSize_t n);
CuAlloc_t *CuAlloc_getHeaderAddr(CuAllocPtr_t ptr);
CuAllocPtr_t CuAlloc_getDataAddr(CuAlloc_t*  ptr);CuSize_t CuAlloc_calculateTotalSize(size_t n);

/* Simple Alloc Functions separating error and return values for replacing thorough ones in release version*/
CuError_t _CuAlloc2(size_t n, CuAllocPtr_t **mem);
CuError_t _CuCalloc2(size_t n, CuAllocPtr_t **mem);
CuError_t _CuRealloc2(CuAllocPtr_t* old, CuAllocPtr_t **new, CuSize_t n);

// CUALLOC_INTERNAL_H_INCLUDED
#endif

