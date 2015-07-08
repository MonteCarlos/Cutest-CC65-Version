#include <stdio.h>
#include <stdarg.h>

int getFormatSize(char* format, ...){
	va_list va;
	va_start(va, format);
	return vsnprintf(NULL, 1, format, va);
}

void main(void){
	unsigned int num = ~0;
	unsigned int numdigits = 0x400;
	char *buf = "  ";
	int len = getFormatSize("%x", num);
    printf("$%x, $%x, %d", num, numdigits, len);
}
