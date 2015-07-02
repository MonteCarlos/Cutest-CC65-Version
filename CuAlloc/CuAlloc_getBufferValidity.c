#include "CuAlloc_internal.h"

bool CuAlloc_getBufferValidity(void *ptr){
    register CuAlloc_t* ptr2 = CuAlloc_getHeaderAddr(ptr);
    if (ptr2 -> this != ptr2) return false;
    return ptr2-> isvalid;
}

