
#include "CuAlloc_internal.h"

void *CuAlloc_getDataAddr(CuAlloc_t* ptr){
	return &(ptr->array);
}
