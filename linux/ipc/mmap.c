#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("mapfile", O_RDWR|O_TRUNC|O_CREAT, 0664);

    if ( fd == -1 ) {
        perror("open error: ");
        exit(1);
    }

    ftruncate(fd, 10);
    int len = lseek(fd, 0, SEEK_END);
    char *mp;

    mp = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if ( mp == MAP_FAILED ) {
       perror("mmap error: ") ;
       exit(1);
    }
    strcpy(mp, "helloworld");

    int ret = munmap(mp, len);
    if ( ret == -1 ) {
        perror("munmap error: ");
        exit(1);
    }

    return 0;
}
