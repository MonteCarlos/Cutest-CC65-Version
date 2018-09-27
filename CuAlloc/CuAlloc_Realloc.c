#include "CuAlloc_internal.h"


void *CuRealloc(void* old, CuSize_t n){
    assert (old); // keep assert and if for DBG/RLS
    if (old==NULL){
        return CuAlloc(n);
    }else{
        register CuAlloc_t* ptr = CuAlloc_getHeaderAddr(old);

        switch (CuAlloc_getBufferValidity(old)){
         case true:
            // @todo (mc78#1#09/22/18): May cause dangling pointer if realloc fails!!!
            CuAlloc_t *ptr2 = (CuAlloc_t*)malloc(CuAlloc_calculateTotalSize(n));
            if (ptr2){
                memset(ptr1, 0x55, CuAlloc_getTotalSize(ptr));
                free(ptr1);
                ++realloccount;
                CuAlloc_initHeader(ptr2, n);
                return CuAlloc_getDataAddr(ptr2);
            }
         default: return NULL;
        }
    }
}

