#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/** \brief Returns CuString buffer size
 *
 * \param CuString* str
 * \return CuStringSize_t buffer size or ~0 on error
 *
 */
CuStringSize_t CuStringSize(CuString *str){
	if (str){
		return str -> size;
	}
	return ~0;
}
