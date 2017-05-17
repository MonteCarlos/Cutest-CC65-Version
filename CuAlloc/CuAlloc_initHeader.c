
#include "CuAlloc_internal.h"

CuError_t CuAlloc_initHeader(CuAlloc_t* ptr, CuSize_t n){
	if (ptr){
		ptr -> totalsize = CuAlloc_calculateTotalSize( (ptr -> this = ptr) -> datasize = n);
		ptr -> data = &(ptr->array);
		ptr -> dataOffset = offsetof(CuAlloc_t, array);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
