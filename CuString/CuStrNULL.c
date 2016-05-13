
#include "CutestString_internal.h"

char* CuStrNULL(const char* const str){
	if (NULL == str){
		return "NULL";//constStr_NULL;
	}
	return (char*)str;
}
