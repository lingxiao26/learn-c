#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strim(const char *src, char *dst);
int getkbyv(const char *kv, char *k, char *v);
/*------------------------------------------------*/
/*
*   键值对解析
*   要求:
*       1. 根据key获取value
*       2. 去除键值对中间的空格
*-------------------------------------------------*/
/* 函数说明:                 */
/*   kv: 传入的kv字符串      */
/*   k: 传入的key            */
/*   v: 传出的value          */
int getkbyv(const char *kv, char *k, char *v)
{
    char *tmp = NULL;
    /* 判断参数的合法性 */
    if ( kv == NULL || k == NULL || v == NULL ) {
        fprintf(stderr, "input is NULL!\n");
        return -1;
    }
    /* 判断kv中是否有k */
    if ( strstr(kv, k) == NULL ) {
        fprintf(stderr, "key not found!\n");
        return -1;
    }
    /* 判断kv中是否有等号 */
    if ( strstr(kv, "=") == NULL ) {
        fprintf(stderr, "kv is invalid!\n");
        return -1;
    }
    /* 找到等号右边的value并去掉两端空格 */
    tmp = strstr(kv, "=") + 1;
    strim(tmp, v);
    return 0;
}

/* 去除字符串两端的空格 */
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
    char *kv = "name=  xiao ";
    char *k = "name";
    char v[30] = {0};
    getkbyv(kv, k, v);

    printf("[%s]: [%s]\n", k, v);

    return 0;
}
