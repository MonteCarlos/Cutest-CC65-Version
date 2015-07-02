#include "CuAlloc_internal.h"

CuAlloc_t *CuAlloc_getHeaderAddr(void* ptr){
	return (CuAlloc_t*)((uint8_t*)ptr-sizeof(CuAlloc_BufHeader_t));
}
