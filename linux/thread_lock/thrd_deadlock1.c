#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


int main(void)
{
    pthread_t tid;
    pthread_mutex_t mutex;
    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    while ( 1 ) {
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&mutex);
        printf("HELLO ");
        sleep(rand()%3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%3);
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}
