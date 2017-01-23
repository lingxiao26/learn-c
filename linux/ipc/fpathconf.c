#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/* 查看资源限制，跟ulimit -a显示的数据类似 */

int main(void)
{
    int fd[2];
    pipe(fd);

    long size = fpathconf(fd[0], _PC_PIPE_BUF);
    if ( size == -1 ) {
        perror("fpathconf error: ");
        exit(1);
    }
    printf("pipe buf: %ld\n", size);

    return 0;
}

