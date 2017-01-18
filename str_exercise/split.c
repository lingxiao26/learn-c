#include <stdio.h>
#include <string.h>

/* 把一个字符串的奇数位和偶数位分别挑选出来组成两个字符串 */

int split(char *src, char *buf1, char *buf2)
{
    char *p = src;
    char *tmp1 = buf1;
    char *tmp2 = buf2;
    int i = 0;

    if ( src == NULL || buf1 == NULL || buf2 == NULL ) {
        fprintf(stderr, "input is NULL!\n");
        return -1;
    }
    for ( i=0; i<strlen(src); i++ ) {
        if ( i%2 == 0 ) {
            *tmp2++ = p[i];
        } else {
            *tmp1++ = p[i];
        }
    }
}

int main(void)
{
    char *str = "1a2b3c4d5e6f7g8h";
    char buf1[10] = {0};
    char buf2[10] = {0};
    split(str, buf1, buf2);
    printf("buf1: %s\nbuf2: %s\n", buf1, buf2);

    return 0;
}
