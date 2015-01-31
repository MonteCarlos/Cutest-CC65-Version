#include "CuAlloc_internal.h"

unsigned long int CuAlloc_getPendingFrees(void){
    return alloccount-freecount;
}
