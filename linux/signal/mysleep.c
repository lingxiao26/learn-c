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

    alarm(seconds);
    pause();

    unsigned int unslept;
    /* 取消闹钟 <== 举一个生活中的栗子来说明该行的作用 */
    /* 晚上睡觉时你定一个早上九点的闹钟，但是早上八点你爸叫你起来去打酱油，这时候你为了闹钟不会在九点响起，会手动把闹钟给取消 */
    unslept = alarm(0);
    /* 恢复信号SIGALRM的默认处理动作 */
    sigaction(SIGALRM, &oldact, NULL);

    return unslept;
}

int main(void)
{
    mysleep(5);

    printf("hello world!\n");

    return 0;
}
