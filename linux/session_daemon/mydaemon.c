#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void mydaemon(void)
{
    pid_t pid, sid;
    pid = fork();
    if ( pid == -1 ) {
        perror("fork error: ");
        exit(1);
    } else if ( pid > 0 ) {
        exit(1);
    }
    sid = setsid();
    if ( sid == -1 ) {
        perror("setsid error: ");
        exit(1);
    }
    int ret = chdir("/");
    if ( ret == -1 ) {
        perror("chdir error: ");
        exit(1);
    }
    umask(0022);
    close(STDIN_FILENO);
    int fd = open("/dev/null", O_RDWR);
    if ( fd == -1 ) {
        perror("open error: ");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    return ;

}

int main(void)
{
    mydaemon();
    while ( 1 );

    return 0;
}
