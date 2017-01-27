#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo)
{
    /* 在该函数执行期间，SIGQUIT信号被屏蔽，如果发送了SIGQUIT信号，函数结束后，SIGQUIT信号将被递达 */
    sleep(5);
    printf("signal %d is under arrest...!\n", signo);
}

int main(void)
{
    /* 自定义一个SIGQUIT阻塞信号集 */
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);

    /* 在信号捕捉函数期间屏蔽SIGQUIT信号 */
    struct sigaction act, oldact;
    act.sa_handler = handler;
    act.sa_mask = set;
    act.sa_flags = 0;

    sigaction(SIGINT, &act, &oldact);

    while (1);

    return 0;
}
