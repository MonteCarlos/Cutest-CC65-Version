#include "CuAlloc_internal.h"

bool CuFree(void *ptr){
    assert (ptr); //makes no sense to pass NULL ptr to free
    if (ptr){
        assert (CuAlloc_getBufferValidity(ptr)); // assert, that valid buffer is passed
        if ( !CuAlloc_getBufferValidity(ptr) ){
            return false;
        }else{
            CuAlloc_t *ptr2 = CuAlloc_getHeaderAddr(ptr);
            memset(ptr2, 0x55, CuAlloc_getTotalSize(ptr2)); //Fill mem to indicate that it has been released
            //(uintptr_t)ptr -= sizeof(CuAlloc_BufHeader_t);
            //assert( ptr2 -> isvalid );

        //    if ( ptr2 -> this != ptr2) return false;
            //ptr2 -> dataOffset = 2*offsetof(CuAlloc_t, data);//invalidate buffer
            free(ptr2);//only free on ptr2 because data is stored in var len arr, which is allocated together with the struct
            ++freecount;
            lastFreed[0] = ptr2;

            return true;
        }
	}
	return false;
}
