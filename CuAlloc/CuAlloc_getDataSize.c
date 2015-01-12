#include "CuAlloc_internal.h"

size_t CuAlloc_getDataSize(void *ptr){
    return ( (CuAlloc_t*)((uint8_t*)ptr-sizeof(CuAlloc_BufHeader_t)) ) -> datasize;
}
