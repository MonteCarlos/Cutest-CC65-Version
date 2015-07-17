#include "CuAlloc_internal.h"

void *CuCalloc(size_t n){
    CuAlloc_t* ptr = (CuAlloc_t*)calloc(CuAlloc_calculateTotalSize(n),1);
    assert(NULL!=ptr);
    CuAlloc_initHeader(ptr, n);

    ++alloccount;
    return CuAlloc_getDataAddr(ptr);
}

