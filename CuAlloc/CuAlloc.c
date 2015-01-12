#include "CuAlloc_internal.h"

void *CuAlloc(size_t n){
    register CuAlloc_t* ptr = (CuAlloc_t*)malloc(n+sizeof(CuAlloc_t));
    assert(NULL!=ptr);
    ptr -> datasize = n;
    ptr -> totalsize = n+sizeof(CuAlloc_t);
    ptr -> isvalid = true;
    return &ptr->array;
}
