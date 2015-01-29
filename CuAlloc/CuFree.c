#include "CuAlloc_internal.h"

bool CuFree(void *ptr){
    uint8_t *ptr2 = (uint8_t*)ptr-sizeof(CuAlloc_BufHeader_t);
    //(uintptr_t)ptr -= sizeof(CuAlloc_BufHeader_t);
    assert( ((CuAlloc_t*)ptr2) -> isvalid );
    ((CuAlloc_t*)ptr2) -> isvalid = false;
    free(ptr2);
    ++freecount;
    return true;
}
