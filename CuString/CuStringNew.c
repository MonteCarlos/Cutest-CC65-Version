
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/** \brief Allocates new CuString struct
 *
 * \param
 * \return CuString* empty CuString
 *
 */
CuString* CuStringNew(void)
{
	CuString* str = (CuString*) CuAlloc(sizeof(CuString));
	assert(NULL!=str);
	CuStringInit(str);

    return str;
}
