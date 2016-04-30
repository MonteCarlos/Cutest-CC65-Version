#include "CuAlloc_internal.h"

void *CuAllocGetLastFreedMem(uint8_t idx){
	return lastFreed[idx];
}
