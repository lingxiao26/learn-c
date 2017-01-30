#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* pid_t getsid(pid_t pid): 获取进程所属session ID */

int main(void)
{
    pid_t pid, sid;
    pid = fork();

    if ( pid > 0 ) {
        printf("I'm the parent %d, pgid: %d\n", getpid(), getpgrp());
        printf("parent session ID: %d\n", getsid(0));
        //setpgid(pid, pid);        /* 设置子进程为进程组的组长 */
        wait(NULL);
    } else if ( pid == 0 ) {
        sleep(1);
        printf("============== child ==============\n");
        printf("I'm the child %d, pgid: %d\n", getpid(), getpgrp());
        printf("child session ID: %d\n", getsid(0));

        sid = setsid();     /* 创建会话ID，创建会话的进程不能为其所属进程组的组长 */
        if ( sid == -1 ) {
            perror("setsid: ");
            exit(1);
        } else {
            printf("new session ID: %d\n", sid);
        }
    }

    return 0;
}
