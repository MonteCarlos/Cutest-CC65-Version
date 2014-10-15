#ifndef CUTESTSTRING_H
#define CUTESTSTRING_H

#include <stdarg.h>
#include <setjmp.h>

#define CUTEST_VERSION  "CuTest 1.5"

/* CuString */

char* CuStrAlloc(int size);
char* CuStrCopy(const char* old);

#define CU_ALLOC(TYPE)		((TYPE*) malloc(sizeof(TYPE)))

#define HUGE_STRING_LEN	512
#define STRING_MAX		256
#define STRING_INC		256

typedef struct
{
	int length;
	int size;
	char* buffer;
} CuString;

void CuStringInit(CuString* str);
CuString* CuStringNew(void);
void CuStringRead(CuString* str, const char* path);
void CuStringAppend(CuString* str, const char* text);
void CuStringAppendChar(CuString* str, char ch);
void CuStringAppendFormat(CuString* str, const char* format, ...);
void CuStringInsert(CuString* str, const char* text, int pos);
void CuStringResize(CuString* str, int newSize);
void CuStringDelete(CuString* str);

char* CuStringCStr(CuString* str);
void CuStringAppendLineFile(CuString* str, char* file, unsigned long int line);
void CuStringComposeMessage(CuTest *tc, CuString* str, char* msg1, char* msg2, char* file, unsigned long int line);
void CuStringAppendULong(CuString *str, unsigned long int num);

#endif /* CUTESTSTRING_H */
