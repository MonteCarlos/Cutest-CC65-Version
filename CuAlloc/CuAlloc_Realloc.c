#include "CuAlloc_internal.h"


void *CuRealloc(void* old, size_t n){
    if (old==NULL){
        return CuAlloc(n);
    }
    {
        register CuAlloc_t* ptr = CuAlloc_getHeaderAddr(old);

        switch (ptr -> isvalid){
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

