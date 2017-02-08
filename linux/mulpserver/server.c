#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <strings.h>
#include <fcntl.h>
#include <signal.h>

/* socket多进程模型 */

#define SERV_PORT 8000

void do_sig(int num)
{
    /* 信号不排队，如果多个子进程同时退出，不是用循环将只能回收一个子进程 */
    while ( waitpid(0, NULL, WNOHANG) )
    ;
}

int main(void)
{
    int lfd, cfd;
    int len, i, cport;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_len;
    pid_t pid;
    char buf[1024], client_ip[128]={0};
    struct sigaction act;

    /* 使用信号回收子进程 */
    act.sa_handler = do_sig;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, NULL);

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

        pid = fork();
        if ( pid == 0 ) {       /* child process */
            /* 关闭socket建立的套接字 */
            close(lfd);

            while ( 1 ) {       /* 收发数据 */
                len = read(cfd, buf, sizeof(buf));
                if ( len == -1 ) {
                    break;
                }
                for ( i=0; i<len; i++ ) {
                    buf[i] = toupper(buf[i]);
                }
                write(cfd, buf, len);
            }

            close(cfd);
            return 0;
        } else if ( pid > 0 ) {     /* parent process */
            close(cfd);
        } else {
            perror("fork error: ");
            exit(1);
        }
    }
    return 0;
}
