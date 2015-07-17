#include "CuAlloc_internal.h"

bool CuAlloc_getBufferValidity(void *ptr){
    CuAlloc_t* ptr2 = CuAlloc_getHeaderAddr(ptr);
    //return (ptr2 -> this == ptr2);
    return (ptr2 -> this != ptr2)?false:ptr2-> isvalid;
}

