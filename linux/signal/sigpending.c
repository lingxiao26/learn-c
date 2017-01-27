#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void printset(sigset_t *pend)
{
    int i;
    for ( i=1; i<32; i++ ) {
        if ( sigismember(pend, i) == 1 ) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
    printf("\n");
}

int main(void)
{
    sigset_t set, oldset, pend;
    
    /* 自定义信号集并清空 */
    sigemptyset(&set);
    /* 添加信号 */
    sigaddset(&set, SIGINT);

    /* 设置上述信号到信号屏蔽字(阻塞信号集) */
    sigprocmask(SIG_BLOCK, &set, &oldset);

    while ( 1 ) {
        sigpending(&pend);      /* 输出未决信号集 */
        printset(&pend);        /* 打印未决信号集 */
        sleep(1);
    }
    /* 程序执行后使用ctrl+c向进程传递SIGINT信号，此时未决信号集编号为2的信号值从0变为1，*/
    /* 但由于阻塞信号集该位也为1，所以SIGINT被阻塞，未能递达 -------------------------- */

}
