#define mkstr(x) #x
#define FILEMAC __FILE__
#define appendcolon FILEMAC ":"

#include <stdio.h>

#define NAME "Stefan"

#define STR(x) #x
#define HELP(x) STR(x)
#define MYFILE HELP(__FILE__) ":"

void main(void){
	char text[sizeof(__FILE__)] = __FILE__;
	//char* text = "first" " second";
	puts(text);
	printf("Strsize: %d %d", sizeof(__FILE__), sizeof(text));
}
