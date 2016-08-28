
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/** \brief clears contents of CuString
 *
 * \param CuString str
 * \return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 *
 */
int CuStringClear(CuString* str)
{
    CuFree(str->buffer);
    CuStringInit(str);
	return EXIT_SUCCESS;
}

