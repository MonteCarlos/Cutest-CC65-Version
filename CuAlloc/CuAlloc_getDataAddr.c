
#include "CuAlloc_internal.h"

void *CuAlloc_getDataAddr(CuAlloc_t* ptr){
	if (ptr) {
		return &(ptr->array);
	}
	return NULL;
}
