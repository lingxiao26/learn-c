#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int strim(const char *src, char *dst)
{
    char *p = NULL;
    char *q = NULL;
    p = (char *)src;
    q = p + strlen(p) - 1;
    if (src == NULL && dst == NULL) {
        fprintf(stderr, "src or dst is NULL!\n");
        return -1;
    }
    while ( isspace(*p) ) {
        p++;
    }
    while ( isspace(*q) && *q != '\0' ) {
        q--;
    }
    strncpy(dst, p, q-p+1);
    return 0;
}

int main(void)
{
    char *str = "      hello world  ";
    char *dst = (char *)malloc(sizeof(char)*30);
    strim(str, dst);
    printf("dst:%s\n", dst);

    return 0;
}
