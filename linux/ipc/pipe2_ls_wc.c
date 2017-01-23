#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/* 兄弟进程间实现 ls | wc -l 的效果 */
/* 用到的函数: execlp dup2 pipe */

int main(void)
{
    pid_t pid;
    int fd[2];
    int ret, i, j;

    ret = pipe(fd);
    if ( ret == -1 ) {
        perror("pipe error: ");
        exit(1);
    }

    for ( i=0; i<2; i++ ) {
        pid = fork();
        if ( pid==0 )
            break;
    }

    if ( 2 == i ) {                 /* 父进程 */
        close(fd[0]);
        close(fd[1]);
        while ( i-- ){
            if( wait(NULL) == -1 ) {
                perror("wait error: ");
                exit(1);
            }                  /* 回收子进程 */
        }
    } else if ( 0 == i ) {         /* 兄进程 */
        close(fd[0]);                /* 关闭读端 */
        dup2(fd[1], STDOUT_FILENO);  /* 标准输出重定向到写端 */
        execlp("ls", "ls", NULL);    
    } else if ( 1 == i){                        /* 弟进程 */
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}

/* 该程序的缺陷：                              */
/*      1. 兄进程的写端和弟进程的读端未关闭    */
