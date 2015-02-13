#include "CuAlloc_internal.h"

bool CuAlloc_getBufferValidity(void *ptr){
    register CuAlloc_t* ptr2 = (CuAlloc_t*)((uint8_t*)ptr-sizeof(CuAlloc_BufHeader_t));
    if (ptr2 -> this != ptr2) return false;
    return ptr2-> isvalid;
}

