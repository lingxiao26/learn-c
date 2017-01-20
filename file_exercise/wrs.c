#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 通过fputs和fgets读写文件 */

int write_s(char *path, char *str, char *type/* "w" or "a" */)
{
    int ret = 0;
    FILE *fp = fopen(path, type);
    if ( fp == NULL ) {
        fprintf(stderr, "fopen %s error!\n", path);
        ret = -1;
    }
    if ( fputs(str, fp) == EOF ) {
        fprintf(stderr, "fputs %s error!\n", path);
        ret = -2;
    }
    fclose(fp);
    return ret;
}

int read_s(char *path)
{
    int ret = 0;
    FILE *fp = fopen(path, "r");
    char buf[1024] = {0};
    if ( fp == NULL ) {
        fprintf(stderr, "fopen %s error!\n", path);
        ret = -1;
    }
    while ( fgets(buf, 1024, fp) != NULL ) {
        printf("%s", buf);
    }
    fclose(fp);
    return ret;
}

int main(void)
{
    char *path = "./test.txt";
    char *str = "maybe oneday, you meet me again\nYou will knonw\nI'm the hero!\n";
    write_s(path, str, "a");
    read_s(path);

    return 0;
}
