#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
        fprintf(stderr, "%s: no such fifo\n", argv[1]);
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if ( fd == -1 ) {
        perror("open error: ");
        exit(1);
    }

    while ( ret=read(fd, buf, sizeof(buf)) ) {
        write(STDOUT_FILENO, buf, ret);
        sleep(1);
    }

    close(fd);

    return 0;
}
