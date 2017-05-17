#include "CuAlloc_internal.h"

CuSize_t CuAlloc_getPendingFrees(void){
    return alloccount-freecount;
}
