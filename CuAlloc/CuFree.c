#include "CuAlloc_internal.h"

bool CuFree(void *ptr){
    if (ptr){
		CuAlloc_t *ptr2 = CuAlloc_getHeaderAddr(ptr);
		//(uintptr_t)ptr -= sizeof(CuAlloc_BufHeader_t);
		//assert( ptr2 -> isvalid );
		if ( !CuAlloc_getBufferValidity(ptr) )  return false;
	//    if ( ptr2 -> this != ptr2) return false;
		ptr2 -> dataOffset = 2*offsetof(CuAlloc_t, data);//invalidate buffer
		free(ptr2);//only free on ptr2 because data is stored in var len arr, which is allocated together with the struct
		++freecount;
		lastFreed[0] = ptr2;

		return true;
	}
	return false;
}
