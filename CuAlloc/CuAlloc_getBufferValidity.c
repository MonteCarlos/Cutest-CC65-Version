#include "CuAlloc_internal.h"

bool CuAlloc_getBufferValidity(void *ptr){
    CuAlloc_t* ptr2 = CuAlloc_getHeaderAddr(ptr);
    //return (ptr2 -> this == ptr2);
    return ((uint8_t*)(ptr2 -> this) + ptr2 -> dataOffset) == (uint8_t*)(ptr2 -> data);
}

