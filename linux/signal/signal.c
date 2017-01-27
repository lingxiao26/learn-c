#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo)
{
    printf("%s signal is under arrest...!\n");
}

int main(void)
{
    signal(SIGINT, handler);

    while ( 1 );

    return 0;
}
