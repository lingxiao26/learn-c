#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fputc & fgetc */

int write_c(char *path, char *str, char *type)
{
    int i;
    FILE *fp = fopen(path, type);
    if ( fp == NULL ) {
        fprintf(stderr, "fopen %s error!\n", path);
        return -1;
    }
    for ( i=0; i<strlen(str); i++ ) {
        if( fputc(str[i], fp) == EOF ) {
            fprintf(stderr, "fputc %s error!\n", path);
            return -1;
        }
    }
    fclose(fp);
    return 0;
}

int read_c(char *path)
{
    int i = 0;
    char ch = 0;
    char buf[1024] = {0};
    FILE *fp = fopen(path, "r");
    if ( fp == NULL ) {
        fprintf(stderr, "fopen %s error!\n", path);
        return -1;
    }
    while ( (ch=fgetc(fp)) != EOF ) {
        buf[i++] = ch;
    }
    printf("read from %s:\n%s\n", path, buf);
    fclose(fp);

    return 0;
}
    
int main(void)
{
    char *path = "./test.txt";
    char *str = "hello putc!";
    write_c(path, str, "w");
    read_c(path);

    return 0;
}
