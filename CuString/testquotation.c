#include <stdio.h>

void main(void){
	unsigned long num = ^0;
	unsigned int numdigits;

	sprintf(NULL, "%n%ul", &numdigits, num);
    printf("%ul, %u", num, numdigits)
}
