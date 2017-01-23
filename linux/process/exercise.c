#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid, wpid;
    int i, status;

    for ( i=0; i<3; i++ ) {
        pid = fork();
        if ( pid==0 ) {
            break;
        }
    }

    sleep(i);

    if ( 3==i ) {
        /* 父进程 */
        while ( i-- ) {
            wpid = waitpid(-1, &status, 0);
            if ( WIFEXITED(status) ) {
                printf("child %d's exit status: %d\n", wpid, WEXITSTATUS(status));
            } else if ( WIFSIGNALED(status) ) {
                printf("child %d's term signal: %d\n", wpid, WTERMSIG(status));
            }
        }
    } else if ( 0==i ){
        execlp("ps", "ps", "a", "u", "x", NULL);
        perror("execlp");
        exit(1);
    } else if ( 1==i ) {
        execl("./test1", "./test1", NULL);
        perror("execl");
        exit(2);
    } else {
        execl("./test2", "./test2", NULL);
        perror("execl");
        exit(3);
    }

    return 0;
}
