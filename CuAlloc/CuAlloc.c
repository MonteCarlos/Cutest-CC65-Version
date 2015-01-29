#include "CuAlloc_internal.h"


unsigned long int alloccount=0;
unsigned long int freecount=0;
unsigned long int realloccount=0;

void *CuAlloc(size_t n){
    register CuAlloc_t* ptr = (CuAlloc_t*)malloc(n+sizeof(CuAlloc_BufHeader_t));
    assert(NULL!=ptr);
    ptr -> datasize = n;
    ptr -> totalsize = n+sizeof(CuAlloc_t);
    ptr -> isvalid = true;
    ++alloccount;
    return &ptr->array;
}
