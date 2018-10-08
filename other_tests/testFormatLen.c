#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE *file = fopen("NULL", "w");

    size_t n = fprintf(file, "Name:%s, Alter:%d", "test", 32);
    printf("Format Str expands to #%d characters", n);
    fclose(file);
}
