#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE(a) (sizeof(a)/sizeof(*a))

/* 找到数组中指定字符串的位置 */
int searchkeypos(const char *keys[], const int size,\
                const char *key, int *pos)
{
    int i, ret=0;
    if ( keys==NULL || key==NULL || pos==NULL) {
        fprintf(stderr, "input is NULL!\n");
        return -1;
    }
    for ( i=0; i<size; i++ ) {
        if ( strcmp(keys[i], key) == 0 ) {
            *pos = i;
        } 
    }
    if ( i == size ) {
        ret = -1;
    }
    return ret;
}

int main(void)
{
    int pos = 0, ret;
    char *keys[] = {
        "python",
        "java",
        "c++",
        "javascript"
    };
    ret = searchkeypos((const char **)keys, SIZE(keys), "xxx", &pos);
    if ( ret == 0 ) {
        printf("pos: %d\n", pos);
    } else {
        printf("未找到!\n");
    }

    return 0;
}
