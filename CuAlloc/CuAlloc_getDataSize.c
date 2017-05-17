#include "CuAlloc_internal.h"
CuSize_t CuAlloc_getDataSize(void *ptr){
    if (ptr){
		return CuAlloc_getHeaderAddr(ptr) -> datasize;
	}
	return ~0;
}
