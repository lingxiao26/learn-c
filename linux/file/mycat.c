#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int cat(char *file)
{
    char buf[1024] = {0};
    int ret = 0;
    int fd = open(file, O_RDWR);
    if ( fd == -1 ) {
        fprintf(stderr, "open %s error!\n", file);
        return -1;
    }
    while ( (ret=read(fd, buf, sizeof(buf))) != 0 ) {
        write(STDOUT_FILENO, buf, ret);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if ( argc != 2 ) {
        fprintf(stderr, "Usage: %s arg1\n", __FILE__);
        return -1;
    }
    char *file = argv[1];

    cat(file);

    return 0;
}
