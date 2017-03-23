#ifndef CUMALLOCWRAPPER_H_INCLUDED
#define CUMALLOCWRAPPER_H_INCLUDED

#include <stdlib.h>

#define malloc(n) CuAlloc(n)
#define calloc(n,m) CuCalloc((n)*(m))
#define realloc(p,n) CuRealloc(p,n)
#define free(p) CuFree(p)

#endif // CUMALLOCWRAPPER_H_INCLUDED
