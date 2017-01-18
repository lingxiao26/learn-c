#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int recurse(char *str)
{
    if ( str == NULL ) {
        return -1;
    }
    /* 递归退出条件 */
    if ( *str == '\0' ) {
        return 0;
    }
    recurse(str+1);
    printf("%c\n", *str);

    return 0;
}

int main(void)
{
    char *str = "hello";
    recurse(str);

    return 0;
}
