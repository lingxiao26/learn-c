#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 计算文件的大小 */

int file_size(char *path)
{
    int ret = 0;
    int head = 0, tail = 0;
    FILE *fp = fopen(path, "r");
    if ( fp == NULL ) {
        fprintf(stderr, "fopen %s error!\n", path);
        ret = -1;
    }
    if ( fseek(fp, 0, SEEK_SET) == 0 ) {
        head = ftell(fp);
    }
    if ( fseek(fp, 0, SEEK_END) == 0 ) {
        tail = ftell(fp);
    }
    ret = tail - head;
    fclose(fp);
    return ret;
}

int main(void)
{
    char *path = "/etc/passwd";
    int size = 0;
    size = file_size(path);
    printf("%s size: %d bytes\n", path, size);

    return 0;
}
