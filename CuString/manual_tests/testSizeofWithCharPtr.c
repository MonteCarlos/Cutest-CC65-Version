#include <stdio.h>
#include <string.h>

typedef char charArr[];

int main(void){
	static charArr *text = {"1234567890"};

	printf("strlen: %d, sizeof: %d", strlen((char*)text), sizeof(*text));
	return 0;
}
