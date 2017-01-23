#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if ( pid == 0 ) {
        printf("I'm the child: %d.\n", getpid());
        sleep(9);
    } else if ( pid > 0 ) {
        while ( 1 ) {
            printf("I'm the parent: %d\n", getpid());
            sleep(1);
        } 
    } else {
        perror("fork error!\n");
        exit(1);
    }

    return 0;
}
