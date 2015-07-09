
#include "CutestString_internal.h"

char* CuStrNULL(const char* const str){
	if (NULL == str){
		return "NULL";
	}
	return (char*)str;
}
