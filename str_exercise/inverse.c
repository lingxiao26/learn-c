#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int inverse(char *src)
{
    char *begin = src;
    char *end = begin + strlen(src) -1;
    char tmp = 0;

    if ( src == NULL ) {
        fprintf(stderr, "src is NULL!\n");
        return -1;
    }

    while ( end > begin ) {
        tmp = *end;
        *end = *begin;
        *begin = tmp;
        end--;
        begin++;
    }
    return 0;
}

int main(void)
{
    char str[] = "hello world!";

    if( inverse(str) == 0 ) {
        printf("str: [%s]\n", str);
    }

    return 0;
}
