#include "CuAlloc_internal.h"
CuSize_t CuAlloc_getTotalSize(CuAllocUserDataPtr_t ptr){
    if (ptr){
        // Use this assertion to verify that ptr is really a ptr to a datablock preceded by header
        assert (CuAlloc_getBufferValidity(CuAlloc_getHeaderAddr(ptr)));
		return CuAlloc_getHeaderAddr(ptr) -> totalsize;
	}
	return ~0;
}

