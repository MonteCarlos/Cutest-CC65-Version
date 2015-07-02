
#include "CuAlloc_internal.h"

void CuAlloc_initHeader(CuAlloc_t* ptr, size_t n){
	ptr -> totalsize = (ptr -> datasize = n) + sizeof(CuAlloc_t);
    ptr -> isvalid = true;
    ptr -> this = ptr;
}
