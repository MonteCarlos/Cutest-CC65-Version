#include "CuAlloc_internal.h"
CuSize_t CuAlloc_getTotalSize(void *ptr){
    if (ptr){
		return CuAlloc_getHeaderAddr(ptr) -> totalsize;
	}
	return ~0;
}

