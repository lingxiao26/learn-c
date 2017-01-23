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
    pid_t pid, wpid;
    int status;

    pid = fork();

    if ( pid == 0 ) {
        printf("I'm the child: %d\n", getpid());
        sleep(3);
        return 20;
    } else if ( pid > 0 ) {
        /* wpid: 返回的子进程ID， status: 子进程的退出状态 */
        wpid = wait(&status);
        printf("I'm the parent: %d\n", getpid());       /* 阻塞 */
        printf("child process %d is cleaned!\n", wpid);

        if ( WIFEXITED(status) ) {
            printf("exit status: %d\n", WEXITSTATUS(status));
        } else if ( WIFSIGNALED(status) ) {
            printf("term signal: %d\n", WTERMSIG(status));
        }
    }
    return 0;
}
