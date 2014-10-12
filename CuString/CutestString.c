#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CuTest.h"


/*-------------------------------------------------------------------------*
 * CuStr
 *-------------------------------------------------------------------------*/

char* CuStrAlloc(int size)
{
	char* newStr = (char*) malloc( sizeof(char) * (size) );
	assert (NULL != newStr);
	return newStr;
}

char* CuStrCopy(const char* old)
{
	int len = strlen(old);
	char* newStr = CuStrAlloc(len + 1);
	strcpy(newStr, old);
	return newStr;
}

/*-------------------------------------------------------------------------*
 * CuString
 *-------------------------------------------------------------------------*/

char* CuStringCStr(CuString* str){
	return str->buffer;
}

//Use long for line number to be not limited to 65535 lines per file
CuStringAppendLineFile(CuString* str, char* file, unsigned long int line){
	CuStringAppend(str, file);
}

CuStringComposeMessage(CuTest *tc, CuString* str, char* msg1, char* msg2, char* file, unsigned long int line){
	CuStringAppend(str, file);
}

void CuStringInit(CuString* str)
{
	str->length = 0;
	str->size = STRING_MAX;
	str->buffer = (char*) malloc(sizeof(char) * str->size);
	assert(str->buffer != NULL);
	str->buffer[0] = '\0';
}

CuString* CuStringNew(void)
{
	CuString* str = (CuString*) malloc(sizeof(CuString));
	str->length = 0;
	str->size = STRING_MAX;
	str->buffer = (char*) malloc(sizeof(char) * str->size);
	assert(str->buffer != NULL);
	str->buffer[0] = '\0';
	return str;
}

void CuStringDelete(CuString *str)
{
	if (!str) return;
	assert(NULL != str->buffer);
	free(str->buffer);
	assert(NULL != str);
	free(str);
}

void CuStringResize(CuString* str, int newSize)
{
	str->buffer = (char*) realloc(str->buffer, sizeof(char) * newSize);
	assert(str->buffer != NULL);
	str->size = newSize;
}

void CuStringAppend(CuString* str, const char* text)
{
	int length;

	if (text == NULL) {
		text = "NULL";
	}

	length = strlen(text);
	if (str->length + length + 1 >= str->size)
		CuStringResize(str, str->length + length + 1 /*+ STRING_INC*/);
	str->length += length;
	strcat(str->buffer, text);
}

void CuStringAppendChar(CuString* str, char ch)
{
	char text[2];
	text[0] = ch;
	text[1] = '\0';
	CuStringAppend(str, text);
}

void CuStringAppendFormat(CuString* str, const char* format, ...)
{
	va_list argp;
	char *buf = (char*)calloc(HUGE_STRING_LEN, sizeof(char));
	assert (NULL != buf);
	va_start(argp, format);
	vsprintf(buf, format, argp);
	va_end(argp);
	CuStringAppend(str, buf);
	assert(NULL != buf);
	free(buf);
}

void CuStringInsert(CuString* str, const char* text, int pos)
{
	int length = strlen(text);
	if (pos > str->length)
		pos = str->length;
	if (str->length + length + 1 >= str->size)
		CuStringResize(str, str->length + length + 1 /*+ STRING_INC*/);
	memmove(str->buffer + pos + length, str->buffer + pos, (str->length - pos) + 1);
	str->length += length;
	memcpy(str->buffer + pos, text, length);
}

