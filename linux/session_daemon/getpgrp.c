#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* pid_t getpgrp(void): 获取进程组ID ======================== */
/* pid_t getpgid(pid_t pid): 获取指定进程的进程组ID ========= */
/* int setpgid(pid_t pid, pid_t pgid): 设置指定进程的进程组ID */

int main(void)
{
    pid_t pid;

    pid = fork();

    if ( pid > 0 ) {

        printf("I'm the parent %d, pgid: %d\n", getpid(), getpgrp());
        setpgid(pid, pid);      /* 设置子进程为进程组的组长 */
    } else if ( pid == 0 ) {
        printf("I'm the child %d, pgid: %d\n", getpid(), getpgrp());
        sleep(1);
        printf("I'm the child %d, pgid: %d\n", getpid(), getpgrp());
    }

    return 0;
}
