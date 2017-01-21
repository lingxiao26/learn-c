#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MSG_TRY "try again:\n"
#define TIMEOUT "time out!\n"

int main(void)
{
    char buf[10] = {0};
    int fd, ret, i;

    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    if ( fd < 0 ) {
        perror("open file: ");
        exit(1);
    }

    for ( i=0; i<3; i++ ) {
        ret = read(fd, buf, 10);

        if ( ret > 0 ) {
            break;
        }
        if ( errno != EAGAIN ) {
            perror("read /dev/tty: ");
            exit(1);
        }
        write(STDOUT_FILENO, TIMEOUT, strlen(TIMEOUT));
        sleep(1);
    } 

    write(STDOUT_FILENO, buf, ret);
    close(fd);

    return 0;
}
