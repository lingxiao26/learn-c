#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <errno.h>
#include <strings.h>

/*-----------------------------------
 * struct pollfd {
 *      int fd;         文件描述符
 *      short events;   监控的事件
 *      short revents;  监控事件中满足条件返回的时间
 * }
 *----------------------------------*/

#define SERV_PORT 8000      /* socket绑定的端口 */
#define OPEN_MAX 1024       /* 进程能打开的最大文件描述符 */

int main(void)
{
    int lfd, cfd, nready, client_port;
    int i, maxi, len, sfd;
    socklen_t client_len;
    char client_ip[64], buf[1024];
    struct sockaddr_in serv_addr, client_addr;
    struct pollfd client[OPEN_MAX];

    lfd = socket(AF_INET, SOCK_STREAM, 0);

    /* 初始化服务端地址和接口 */
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(lfd, 128);

    client[0].fd = lfd;
    client[0].events = POLLIN;

    for ( i=1; i<OPEN_MAX; i++ ) {
        client[i].fd = -1;
    }
    maxi = 0;       /* 监听的文件描述符个数 */

    for ( ; ; ) {
        /* poll阻塞，等待客户端的连接 */
        nready = poll(client, maxi+1, -1);


        /* -------------  新的客户端连接 --------------- */
        if ( client[0].revents & POLLIN ) {     /* 为真说明有新的客户端连接 */

            client_len = sizeof(client_addr);
            cfd = accept(lfd, (struct sockaddr *)&client_addr, &client_len);

            /*------------ 获取客户端的IP和端口 -----------*/
            client_port = ntohs(client_addr.sin_port);
            inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
            /*--------------------------------------------*/

            printf("client IP: %s PORT: %d\n", client_ip, client_port);

            /* 存储打开的客户端文件描述符 */
            for ( i=1; i<OPEN_MAX; i++ ) {
                if ( client[i].fd < 0 ) {
                    client[i].fd = cfd;
                    break;
                }
            }

            if ( i == OPEN_MAX ) {
                fprintf(stderr, "too many client\n");
                exit(1);
            }

            /* 把刚刚打开的文件描述符设置为监控读事件 */
            client[i].events = POLLIN;

            /* 更新监听的文件描述符个数 */
            if ( i > maxi )
                maxi = i;

            if ( --nready <= 0 )
                continue;
        }
        /* ----------------------------------------- */


        /* ------ 监听的客户端发生了读事件 -------- */
        for ( i=1; i<=maxi; i++ ) {
            if ( (sfd=client[i].fd) < 0 )
                continue;
            if ( client[i].revents & (POLLIN) ) {     /* 判断文件描述符是否处于监听状态 */
                if ( (len=read(sfd, buf, sizeof(buf))) < 0 ) {
                    if ( errno == ECONNRESET ) {
                        /* 客户端异常终止，给服务端发送RST标志 */
                        /* connection reset by client */
                        printf("client[%d] connection aborted\n", i);
                        close(sfd);
                        client[i].fd = -1;
                    } else {
                        perror("read error: ");
                        exit(1);
                    }
                } else if ( len == 0 ) {
                    /* 客户端正常关闭 */
                    printf("client[%d] connection closed\n", i);
                    close(sfd);
                    client[i].fd = -1;
                } else {
                    /* 正常收发数据 */
                    int j;
                    for ( j=0; j<len; j++ )
                        buf[j] = toupper(buf[j]) ;
                    write(sfd, buf, len);
                }
                if ( --nready <= 0 )
                    break;
            }
        }
        /* ---------------------------------------- */
    }


    return 0;
}
