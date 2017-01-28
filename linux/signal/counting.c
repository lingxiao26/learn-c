#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int n = 0, flag = 0;

void do_sig_parent(int signo)
{
     printf("parent: %d, couting: %d\n", getpid(), n);
     n+=2;
     flag = 1;
     //sleep(1);
}

void do_sig_child(int signo)
{
    printf("child:  %d, couting: %d\n", getpid(), n);
    n+=2;
    flag = 1;
    //sleep(1);
}

int main(void)
{
    struct sigaction act;
    pid_t pid;
    int i = 0;

    pid = fork();
    if ( pid > 0 ) {
        sleep(1);

        n = 1;
        do_sig_parent(0);

        act.sa_handler = do_sig_parent;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGUSR2, &act, NULL);
       
        while ( 1 ) {
            if ( flag == 1 ) {
                kill(pid, SIGUSR1);
                // ...失去cpu-->child.do_sig_child-->kill(parent,SIGUSR2)-->parent.do_sig_parent().flag=1-->在该处继续往下执行，之后flag的值将一直为0，阻塞在while（1）处。。
                flag = 0;
            } 
        }
         
    } else if ( pid == 0 ) {
        n = 2;
        act.sa_handler = do_sig_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGUSR1, &act, NULL);

        while ( 1 ) {
            if ( flag == 1 ) {
                kill(getppid(), SIGUSR2);
                flag = 0;
            }
        }
    }
    return 0;
}
