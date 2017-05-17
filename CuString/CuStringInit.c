
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/** \brief Initializes fields of CuString Struct
 *
 * \param CuString* str
 * \return SUCCESS on valie str, FAILURE, otherwise
 *
 */
CuError_t CuStringInit(register CuString* str)
{
	if (str){
		str->length = 0;
		str->size = CUSTRING_LEN_NEW+1;
		//initializes string to zero, too!
		str->buffer = CuStrAlloc(CUSTRING_LEN_NEW);
		assert(str->buffer != NULL);

		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
