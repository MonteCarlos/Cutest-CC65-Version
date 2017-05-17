
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
CuError_t CuStringClear(CuString* str)
{
    if (str){
		CuFree(str->buffer);
		CuStringInit(str);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

