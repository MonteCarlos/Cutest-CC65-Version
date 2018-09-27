#include "CuAlloc_internal.h"


CuSize_t alloccount = 0;
CuSize_t freecount = 0;
CuSize_t realloccount = 0;

void *lastFreed[5] = {0};
void *lastAllocated[5] = {0};

void *CuAlloc (size_t n) {
    register CuAlloc_t *ptr = (CuAlloc_t *) malloc (CuAlloc_calculateTotalSize (n) );

    if ( !ptr ) {
        return NULL;
    }
    else {
        void *data = CuAlloc_getDataAddr (ptr);
        CuAlloc_initHeader (ptr, n);
        memset (data, 0xf0, n);
        ++alloccount;
        return data;
    }
}
