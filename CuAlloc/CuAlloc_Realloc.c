#include "CuAlloc_internal.h"


void *CuRealloc(void* old, CuSize_t n){
    assert (old); // keep assert and if for DBG/RLS
    if (old==NULL){
        return CuAlloc(n);
    }else{
        register CuAlloc_t* ptr = CuAlloc_getHeaderAddr(old);
        CuAlloc_t *ptr2;

        switch (CuAlloc_getBufferValidity(old)){
         case true:
            ptr2 = (CuAlloc_t*)malloc(CuAlloc_calculateTotalSize(n));
            // @todo (mc78#1#09/22/18): May cause dangling pointer if realloc fails!!!
            if (ptr2){
                void *data = CuAlloc_getDataAddr(ptr2);
                memcpy(ptr2, ptr, CuAlloc_calculateTotalSize(n));

                memset(ptr, 0x55, CuAlloc_getTotalSize(ptr)); // Fill memory from previous alloc
                free(ptr); // free memory from previous alloc
                ++realloccount;
                CuAlloc_initHeader(ptr2, n);
                return data;
            }
         default: return NULL;
        }
    }
}

