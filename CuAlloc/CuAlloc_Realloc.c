#include "CuAlloc_internal.h"


void *CuRealloc(void* old, CuSize_t n){
    if (old==NULL){
        return CuAlloc(n);
    }
    {
        register CuAlloc_t* ptr = CuAlloc_getHeaderAddr(old);

        switch (CuAlloc_getBufferValidity(old)){
         case true:
            ptr = realloc(ptr, CuAlloc_calculateTotalSize(n));
            ++realloccount;
            assert(NULL!=ptr);
            CuAlloc_initHeader(ptr, n);
            return CuAlloc_getDataAddr(ptr);
         default: return NULL;
        }
    }
}

