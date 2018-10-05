#include "CuAlloc_internal.h"
CuSize_t CuAlloc_getDataSize(void *ptr){
    if (ptr){
        assert (CuAlloc_getBufferValidity(CuAlloc_getHeaderAddr(ptr)));
		return CuAlloc_getHeaderAddr(ptr) -> datasize;
	}
	return ~0;
}
