#include "CuAlloc_internal.h"

void *CuCalloc(size_t n){
    register CuAlloc_t* ptr = (CuAlloc_t*)calloc(n+sizeof(CuAlloc_BufHeader_t),1);
    assert(NULL!=ptr);
    ptr -> datasize = n;
    ptr -> totalsize = n+sizeof(CuAlloc_t);
    ptr -> isvalid = true;
    ptr -> this = ptr;
    ++alloccount;
    return &(ptr->array);
}

