#include "CuAlloc_internal.h"

CuAlloc_t *CuAlloc_getHeaderAddr(void* ptr){
	if (ptr){
		return (CuAlloc_t*)((uint8_t*)ptr-sizeof(CuAlloc_BufHeader_t));
	}
	return NULL;
}
