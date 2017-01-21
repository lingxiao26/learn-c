#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 阻塞读终端(标准输入) */

int main(void)
{
    char buf[10];
    int ret = 0;

    ret = read(STDIN_FILENO, buf, 10);
    if ( ret == -1 ) {
        perror("read stdin: ");
        exit(1);
    }
    write(STDOUT_FILENO, buf, ret);

    return 0;
}
