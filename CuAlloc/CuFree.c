#include "CuAlloc_internal.h"

bool CuFree(void *ptr){
    CuAlloc_t *ptr2 = (CuAlloc_t*)( (uint8_t*)ptr-sizeof(CuAlloc_BufHeader_t) );
    //(uintptr_t)ptr -= sizeof(CuAlloc_BufHeader_t);
    //assert( ptr2 -> isvalid );
    if ( !(ptr2 -> isvalid) )  return false;
//    if ( ptr2 -> this != ptr2) return false;
    ptr2 -> isvalid = false;
    free(ptr2);
    ++freecount;
    return true;
}
