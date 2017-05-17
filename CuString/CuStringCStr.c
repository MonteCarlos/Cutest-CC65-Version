#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"
/** \brief Returns pointer to CuString buffer containing encapsulated c_str
 *
 * \param CuString* str (CuString from which c_str should be isolated)
 * \return Pointer to char* buffer
 *
 */

char* CuStringCStr(CuString* str){
	if (str){
		return str->buffer;
	}
	return NULL;
}

