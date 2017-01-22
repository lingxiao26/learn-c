#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* dup2: 复制的是文件描述符对应的指针，而不是文件描述符本身 */
/* 可以让标准输出对应的文件描述符的指针指向一个文件改变输出的目的地 也就是重定向 */

int main(void)
{
    int fd1 = open("test/hello", O_RDONLY);
    if ( fd1 == -1 ) {
        perror("open error: ");
        exit(1);
    }
    printf("fd1: %d\n", fd1);

    int fd2 = open("test/world", O_RDONLY);
    if ( fd2 == -1 ) {
        perror("open error: ");
        exit(1);
    }
    printf("fd2: %d\n", fd2);

    int newfd = dup2(fd1, fd2);
    if ( newfd == -1 ) {
        perror("dup2 error: ");
        exit(1);
    }
    printf("newfd: %d\n", newfd);

    close(fd1);
    close(fd2);

    return 0;
}
