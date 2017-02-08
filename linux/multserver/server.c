#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <strings.h>
#include <fcntl.h>
#include <pthread.h>

/* socket多线程模型 */

#define SERV_PORT 8000

void *start_routine(void *arg)
{
    long cfd = (long)arg;
    int len, i;
    char buf[1024];

    /* 把线程变成游离态（子进程结束后不用回收，相当于父进程wait子进程） */
    pthread_detach(pthread_self());

    while ( 1 ) {
        len = read(cfd, buf, sizeof(buf));
        if ( len <= 0 )
            break;
        write(STDOUT_FILENO, buf, len);
        for ( i=0; i<len; i++ ) {
            buf[i] = toupper(buf[i]);
        }
        write(cfd, buf, len);
    }
    close(cfd);
    return (void *)0;
}

int main(void)
{
    int lfd;
    long cfd;
    int len, i, cport;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_len;
    char buf[1024], client_ip[128]={0};
    pthread_t tid;

    lfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(lfd, 128);
    printf("waiting for connect...\n");

    while ( 1 ) {
        client_len = sizeof(client_addr);
        cfd = accept(lfd, (struct sockaddr *)&client_addr, &client_len);
        cport = ntohs(client_addr.sin_port);

        /* 转换客户端的IP，存放在client_ip里 */
        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, &client_ip, sizeof(client_ip));
        printf("client IP: %s\t%d\n", client_ip, cport);

        pthread_create(&tid, NULL, start_routine, (void *)cfd);

    }
    return 0;
}
