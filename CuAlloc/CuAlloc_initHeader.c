
#include "CuAlloc_internal.h"

void CuAlloc_initHeader(CuAlloc_t* ptr, size_t n){
	ptr -> totalsize = CuAlloc_calculateTotalSize( (ptr -> this = ptr) -> datasize = n);
    ptr -> data = &(ptr->array);
    ptr -> dataOffset = offsetof(CuAlloc_t, array);
}
