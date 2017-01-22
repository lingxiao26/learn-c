#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid; 
    int i;

    for ( i=0; i<5; i++ ) {
        if ( (pid=fork()) == 0 ) {
            break;
        }
    }
    if ( 5 == i ) {
        sleep(5);
        printf("I'm the parent: %d\n", getpid());
    } else {
        sleep(i);
        printf("I'm the %dth child: %d, parentID is %d\n", i, getpid(), getppid());
    }

    return 0;
}
