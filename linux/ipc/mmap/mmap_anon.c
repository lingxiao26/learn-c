#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>

int main(void)
{
    char *mp;
    int len = 1024;
    char buf[1024];

    mp = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    if ( mp == MAP_FAILED ) {
       perror("mmap error: ") ;
       exit(1);
    }

    pid_t pid = fork();
    if ( pid > 0 ) {
        int i = 0;
        while ( 1 ) {
            sprintf(buf, "hello world %d\n", i++);
            strcpy(mp, buf);
            sleep(1);
        }
    } else if ( pid == 0 ) {
        while ( mp != NULL ) {
            printf("mmap-> %s\n", mp);
            sleep(1);
        }
    }

    int ret = munmap(mp, len);
    if ( ret == -1 ) {
        perror("munmap error: ");
        exit(1);
    }

    return 0;
}
