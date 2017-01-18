#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------*/
/* 在堆上分配一个字符串数组    */
/* description:                */
/*     num: 分配字符数组的个数 */
/*     size: 字符数组的大小    */
/* return value:               */
/*     char **ret  or NULL     */
/*-----------------------------*/
char **get_mem(int num, int size)
{
    char **ret = NULL;
    int i;

    ret = (char **)malloc(sizeof(char *)*num);
    if ( ret == NULL ) {
        fprintf(stderr, "malloc char **array error\n");
        return NULL;
    }
    memset(ret, 0, sizeof(char *)*num);
    for ( i=0; i<num; i++ ) {
        ret[i] = (char *)malloc(sizeof(char)*size);
        if (ret[i] == NULL) {
            fprintf(stderr, "malloc array[%d] error\n", i);
            return NULL;
        }
    }

    return ret;
}
void free_mem(char **str, int num)
{
    char **tmp = str;
    int i;
    if ( tmp == NULL ) {
        return;
    }
    for ( i=0; i<num; i++ ) {
        if ( tmp[i] != NULL ) {
            free(tmp[i]);
            tmp[i] = NULL;
        }
    } 
    free(tmp);
}

int main(void)
{
    char **str = NULL;
    int num = 4, i;
    int size = 64;

    str = get_mem(num, size);
    printf("str: %p\n", str);
    for (i=0; i<num; i++) {
        /* 注意这里不能直接赋值，否则所分配的内存都指向静态区的同一块内存单元了 */
        strcpy(str[i], "abcdef");
        printf("str[%d]: %s\n", i, str[i]);
    }
    free_mem(str, num);
    str = NULL;

    return 0;
}
