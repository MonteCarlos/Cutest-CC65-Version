#include "CuAlloc_internal.h"

bool CuFree(void *ptr){
    (uint8_t*)ptr -= sizeof(CuAlloc_BufHeader_t);
    assert( ((CuAlloc_t*)ptr) -> isvalid );
    ((CuAlloc_t*)ptr) -> isvalid = false;
    free(ptr);
    return true;
}
