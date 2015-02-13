#include "CuAlloc_internal.h"


void *CuRealloc(void* old, size_t n){
    if (NULL == old){
         return CuAlloc(n);
    }else{
        register CuAlloc_t* ptr = (CuAlloc_t*)((uint8_t*)old-sizeof(CuAlloc_BufHeader_t));

/*    if (ptr -> this != ptr){
        return NULL;
   }*/

        if (ptr -> isvalid){
      //assert(ptr -> isvalid);
                ptr = realloc(ptr, n+sizeof(CuAlloc_BufHeader_t));
                ++realloccount;
                assert(NULL!=ptr);

                ptr -> this = ptr;
                ptr -> datasize = n;
                ptr -> totalsize = n+sizeof(CuAlloc_t);
        //ptr -> isvalid = true;
        //++alloccount;
                return &(ptr->array);
        }
        return NULL;
    }
}

