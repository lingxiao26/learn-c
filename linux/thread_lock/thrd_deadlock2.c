#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

struct {
    int var;
    pthread_mutex_t mutex;
} s1, s2;


void *start_routine(void *arg)
{
    /* 子线程 */
    srand(time(NULL));

    pthread_mutex_lock(&s1.mutex);
    sleep(rand()%3);
    pthread_mutex_lock(&s2.mutex);
    s1.var = 1000;
    printf("subthread ===> s1.var: %d, s2.var: %d\n", s1.var, s2.var);

    return (void *)0;
}

int main(void)
{
    pthread_t tid;
    srand(time(NULL));
    
    s1.var = 100;
    s2.var = 200;
    pthread_mutex_init(&s1.mutex, NULL);
    pthread_mutex_init(&s2.mutex, NULL);

    pthread_create(&tid, NULL, start_routine, NULL);

    /* 主线程 */
    pthread_mutex_lock(&s2.mutex);
    sleep(rand()%3);
    pthread_mutex_lock(&s1.mutex);
    s2.var = 2000;
    printf("main ===> s1.var: %d, s2.var: %d\n", s1.var, s2.var);

    pthread_mutex_destroy(&s1.mutex);
    pthread_mutex_destroy(&s2.mutex);

    return 0;
}
