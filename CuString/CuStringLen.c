#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/** \brief Returns len of c_str contained in CuString struct
 *
 * \param CuString* str
 * \return CuStringLen_t stringlen
 *
 */
CuStringLen_t CuStringLen(CuString *str){
    //assert(str -> length == strlen(str -> buffer));
    //Assert that length field is identical to length of string in buffer
	if (str){
		return str -> length;
	}
	return ~0;
}
