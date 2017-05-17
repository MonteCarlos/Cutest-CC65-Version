#include "CuAlloc_internal.h"


CuSize_t alloccount=0;
CuSize_t freecount=0;
CuSize_t realloccount=0;

void *lastFreed[5] = {0};
void *lastAllocated[5] = {0};

void *CuAlloc(size_t n){
    register CuAlloc_t* ptr = (CuAlloc_t*)malloc(CuAlloc_calculateTotalSize(n));
    assert(NULL!=ptr);
    CuAlloc_initHeader(ptr, n);

    ++alloccount;
    return CuAlloc_getDataAddr(ptr);
}
