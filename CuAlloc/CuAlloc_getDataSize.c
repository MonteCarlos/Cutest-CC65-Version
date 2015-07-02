#include "CuAlloc_internal.h"

size_t CuAlloc_getDataSize(void *ptr){
    return CuAlloc_getHeaderAddr(ptr) -> datasize;
}
