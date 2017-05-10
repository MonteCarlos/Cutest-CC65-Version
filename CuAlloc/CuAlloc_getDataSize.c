#include "CuAlloc_internal.h"
 CuSize_t CuAlloc_getDataSize(void *ptr){
    return CuAlloc_getHeaderAddr(ptr) -> datasize;
}
