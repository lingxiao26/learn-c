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
#include <sys/select.h>


#define SERV_PORT 8000

int main(void)
{
    int lfd, cfd, maxfd, sockfd;
    int nready, client_len;
    int i, client[FD_SETSIZE];
    fd_set readfds, tmpfds;
    struct sockaddr_in serv_addr, client_addr;
    int client_port, len;
    char client_ip[128], buf[1024];

    lfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(lfd, 128);

    maxfd = lfd;

    FD_ZERO(&tmpfds);
    FD_SET(lfd, &tmpfds);

    /* 初始化client[]的最大下标 */
    int maxi = -1;  
    /* 初始化client[FD_SETSIZE] */
    for ( i=0; i<FD_SETSIZE; i++ ) {
        client[i] = -1;
    }

    while ( 1 ) {
        /* 调用select的时候，第二个参数为传入传出参数，函数返回后该参数会发生改变，所以先把该变量赋值给readfds */
        readfds = tmpfds;
        nready = select(maxfd+1, &readfds, NULL, NULL, NULL);
        if ( nready < 0 ) {
            perror("select error: ");
            exit(1);
        }
        if ( FD_ISSET(lfd, &readfds) ) {        /* FD_ISSET(lfd, &readfds) 判断lfd是否为就绪态 */
            /* 如果if为真，说明lfd就绪，是新的连接请求 */
            client_len = sizeof(client_addr);
            cfd = accept(lfd, (struct sockaddr *)&client_addr, &client_len);

            /* 获取客户端的ip和端口 */
            client_port = ntohs(client_addr.sin_port);
            inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
            printf("Received from %s at PORT %d\n", client_ip, client_port);

            /* 保存cfd */
            for ( i=0; i<FD_SETSIZE; i++ ) {
                if ( client[i] < 0 ) {
                    client[i] = cfd;
                    break;
                }
            }

            /* 达到select所能监控的文件个数上限1024 */
            if ( i == FD_SETSIZE ) {
                fprintf(stderr, "too many clients\n");
                exit(1);
            }

            /* 把套接字cfd添加到tmpfds套接字集合中 */
            FD_SET(cfd, &tmpfds);

            /* select的第一个参数是打开的最大的文件描述符加一，如下可保证maxfd为打开的最大的文件描述符 */
            if ( cfd > maxfd )
                maxfd = cfd;

            /* 更新client[]最大下标值 */
            if ( i > maxi ) {
                maxi = i;
            }
        }
        /* for test
        for ( i=0; i<=maxi; i++ ) {
            if ( client[i] > 0 )
                printf("client[%d]: %d\n", i, client[i]);
        }
        */
        for ( i=0; i<=maxi; i++ ) {
            /* 检测那个client有数据就绪 */
            if ( (sockfd=client[i]) < 0 )
                continue;
           
            if ( FD_ISSET(sockfd, &readfds) ) {
                if ( (len=read(sockfd, buf, sizeof(buf))) == 0 ) {
                    /* len==0说明客户端关闭了连接 */
                    close(sockfd);
                    /* 解除select对此文件描述符的监控 */
                    FD_CLR(sockfd, &tmpfds);
                    client[i] = -1;
                } else {
                    int j;
                    for ( j=0; j<len; j++ ) {
                        buf[j] = toupper(buf[j]);
                    }
                    write(sockfd, buf, len);
                }
            }
        }
    }


    return 0;
}
