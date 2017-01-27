#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo)
{
    /* Nothing to do */
}

unsigned int mysleep(unsigned int seconds)
{
    struct sigaction act, oldact;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, &oldact);

    /* alarm为自然计时法，如果程序在调用alarm之后失去cpu，且在seconds时间后还未获得cpu，pause就无法获得SIGALRM信号，程序将一直挂起，这就是时序竞争问题 */
    /* 为了解决这个问题，需在调用alarm函数之前屏蔽alarm信号，把pause函数和解除SIGALRM屏蔽字绑定成一个原子操作 */

    /* 屏蔽alarm信号 */
    sigset_t set, oldset, suspset;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &oldset);

    alarm(seconds);
    /* 解除屏蔽并挂起 */
    suspset = oldset;
    sigdelset(&suspset, SIGALRM);
    sigsuspend(&suspset);

    unsigned int unslept;
    /* 取消闹钟 <== 举一个生活中的栗子来说明该行的作用 */
    /* 晚上睡觉时你定一个早上九点的闹钟，但是早上八点你爸叫你起来去打酱油，这时候你为了闹钟不会在九点响起，会手动把闹钟给取消 */
    unslept = alarm(0);
    /* 恢复信号SIGALRM的默认处理动作 */
    sigaction(SIGALRM, &oldact, NULL);
    sigprocmask(SIG_SETMASK, &oldset, NULL);

    return unslept;
}

int main(void)
{
    mysleep(5);

    printf("hello world!\n");

    return 0;
}
