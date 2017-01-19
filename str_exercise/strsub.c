#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 子字符串替换 -----------------------------------*/
/* Example: -------------------------------------*/
/*      src:     "abc11hello11111hello22222hello3333" */
/*      dst:     "abc11world11111world22222worlddd3333" */
/*      sub:     "hello" ------------------------*/
/*      new_sub: "world" ------------------------*/
/* return: 0 success -1 failed ------------------*/

int substr(/* in */char *src, /* out */char **dst, \
           /* in */char *sub, /* in */char *new_sub)
{
    char *head = src;
    char *tail = head;
    if ( src==NULL || dst==NULL || sub==NULL || new_sub==NULL ) {
        fprintf(stderr, "input is NULL!\n");
        return -1;
    }

    char *out = (char *)malloc(sizeof(char)*4096);
    if (out == NULL) {
        fprintf(stderr, "malloc char error!\n");
        return -1;
    }
    memset(out, 0, 4096);

    while ( (tail = strstr(tail, sub)) != NULL ) {
        strncat(out, head, tail-head);
        strncat(out, new_sub, strlen(new_sub));
        tail += strlen(sub);
        head = tail;
        if ( *tail == '\0' ) {
            break;
        }
    }
    if (*head != '\0') {
        strncat(out, head, src+strlen(src)-head);
    }
    *dst = out;
    return 0;
}

int main(void)
{
    char *str = "abc11hello11111hello22222hello3333";
    char *sub = "hello";
    char *new_sub = "world";
    char *dst = NULL;
    substr(str, &dst, sub, new_sub);
    printf("dst: %s\n", dst);

    return 0;
}
