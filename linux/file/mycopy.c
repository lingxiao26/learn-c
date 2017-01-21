#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int copy(const char *src, char *dst)
{
    char buf[1024] = {0};
    int ret = 0;
    int fd1 = open(src, O_RDONLY);
    int fd2 = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0664);

    if ( fd1 == -1 || fd2 == -1 ) {
        fprintf(stderr, "open %s or %s error!\n", src, dst);
        return -1;
    }
    
    while ( (ret=read(fd1, buf, sizeof(buf))) != 0 ) {
        write(fd2, buf, ret);
    }
    close(fd1);
    close(fd2);
    return 0;
}

int main(int argc, char *argv[])
{
    if ( argc != 3 ) {
        fprintf(stderr, "Usage: %s src dst\n", __FILE__);
        return -1;
    }
    char *src = argv[1];
    char *dst = argv[2];

    copy(src, dst);

    return 0;
}
