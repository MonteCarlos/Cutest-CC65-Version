#include "CuAlloc_internal.h"

size_t CuAlloc_calculateTotalSize(size_t n){
    return n+sizeof(CuAlloc_BufHeader_t);
}

