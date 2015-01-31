#ifndef CUALLOC_INTERNAL_H_INCLUDED
#define CUALLOC_INTERNAL_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include "CuAlloc.h"

typedef struct CuAlloc_BufHeader_tag CuAlloc_BufHeader_t;
typedef struct CuAlloc_tag CuAlloc_t;

struct CuAlloc_BufHeader_tag{
    bool isvalid;
    size_t datasize;
    size_t totalsize;

};

struct CuAlloc_tag {
    CuAlloc_BufHeader_t;//Anonymous Struct
    uint8_t array[];
};

extern unsigned long int alloccount;
extern unsigned long int freecount;
extern unsigned long int realloccount;

#endif // CUALLOC_INTERNAL_H_INCLUDED
