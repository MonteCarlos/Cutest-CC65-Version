#include "CuAlloc_internal.h"

bool CuAlloc_getBufferValidity(void *ptr){
    return ( (CuAlloc_t*)((uint8_t*)ptr-sizeof(CuAlloc_BufHeader_t)) ) -> isvalid;
}

