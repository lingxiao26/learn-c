#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/* 父子进程间实现 ls | wc -l 的效果 */
/* 用到的函数: execlp dup2 pipe */

int main(void)
{
    pid_t pid;
    int fd[2];
    int ret;
    char buf[1024];     /* 子进程从管道读取数据存放的缓存 */

    ret = pipe(fd);
    if ( ret == -1 ) {
        perror("pipe error: ");
        exit(1);
    }

    pid = fork();
    if ( pid > 0 ) {                 /* 父进程 */
        close(fd[1]);                /* 关闭写端 */
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);

    } else if ( pid == 0 ) {         /* 子进程 */
        close(fd[0]);                /* 关闭读端 */
        dup2(fd[1], STDOUT_FILENO);  /* 标准输出重定向到写端 */
        execlp("ls", "ls", NULL);    
    }

    

    return 0;
}

/* 该程序的缺陷：                              */
/*      1. 父进程没有回收子进程                */
/*      2. 父进程的读端和子进程的写端未关闭    */
