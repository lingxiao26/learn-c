#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MSG_TRY "try again:\n"

int main(void)
{
    char buf[10] = {0};
    int fd, ret;

    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    if ( fd < 0 ) {
        perror("open file: ");
        exit(1);
    }
tryagain:
    ret = read(fd, buf, 10);
    if ( ret == -1 ) {
        if( errno != EAGAIN ) {
            perror("read /dev/tty: ");
            exit(1);
        }
        sleep(3);
        write(STDOUT_FILENO, MSG_TRY , strlen(MSG_TRY));
        goto tryagain;
    }
    write(STDOUT_FILENO, buf, ret);
    close(fd);

    return 0;
}
