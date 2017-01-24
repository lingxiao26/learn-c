#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if ( argc != 2 ) {
        fprintf(stderr, "Usage: %s fifoname\n", __FILE__);
        exit(1);
    }

    char buf[4096];
    int ret;
    ret = access(argv[1], F_OK);
    if ( ret == -1 ) {
        if( mkfifo(argv[1], 0664) == -1 ) {
            perror("mkfifo error: ");
            exit(1);
        }
    }

    int fd = open(argv[1], O_WRONLY);
    if ( fd == -1 ) {
        perror("open error: ");
        exit(1);
    }
    int i = 0;
    while ( 1 ) {
        sprintf(buf, "hello world %d\n", i++);
        /*
        if ( write(fd, buf, sizeof(buf)) == -1 ) {
            perror("write error: ");
            exit(1);
        }
        */
        write(fd, buf, strlen(buf));
        sleep(1);
    }

    close(fd);

    return 0;
}
