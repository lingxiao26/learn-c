#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

/* 两个线程同时操作共享资源（标准输出），使用sleep函数导致cpu易主，产生于时间有关的错误 */

void *start_routine(void *arg)
{
    srand(time(NULL));
    for (;;) {
        printf("hello ");
        sleep(rand()%3);
        printf("world\n");
        sleep(rand()%3);
    }
}


int main(void)
{
    pthread_t tid;
    srand(time(NULL));

    pthread_create(&tid, NULL, start_routine, NULL);

    for (;;) {
        printf("HELLO ");
        sleep(rand()%3);
        printf("WORLD\n");
        sleep(rand()%3);
    }

    pthread_join(tid, NULL);

    return 0;
}
