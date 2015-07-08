#include <stdio.h>

void main(void){
	unsigned long int num = ~0;
	unsigned int numdigits = ~0;
	char *buf = "";
	size_t len = snprintf(NULL, 0, "%lu", num);
    printf("%lx, %x, %u", num, numdigits, len);
}
