#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* wait函数的三个作用 */
/* 1. 阻塞等待子进程退出 */
/* 2. 回收子进程残留资源 */
/* 3. 获取子进程结束状态（退出原因） */

int main(void)
{
    pid_t pid, wpid, tmppid;
    int status, i;

    for ( i=0; i<5; i++ ) {
        pid = fork();
        if ( pid==0 ) {
            break;
        }
        if ( i==2 ) {
            tmppid = pid;
        }
    }
    sleep(i);

    if ( 5 == i ) {
        printf("I am parent %d\n", getpid());
        //wpid = waitpid(tmppid, NULL, WNOHANG);
        while ( i-- ) {
            wpid = waitpid(-1, NULL, 0); 
            printf("wpid: %d\n", wpid);
        }
    } else {
        printf("I am the child %d, my parent is %d\n", getpid(), getppid());
    }

    return 0;
}
