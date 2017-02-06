#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <ctype.h>
#include <strings.h>
#include <fcntl.h>

#define SERV_PORT 8000

int main(void)
{
    int sfd, cfd;
    int i, addr_len, len, cport;
    char buf[4096], client_ip[128] = {0};
    struct sockaddr_in serv_addr, client_addr;

    /* 创建一个网络套接字 AF_INET:ipv4  SOCK_STREAM:流式协议  0:默认为tcp */
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    /* 将地址结构体内容清零 */
    bzero(&serv_addr, sizeof(serv_addr));

    /* 初始化地址结构体 */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* 绑定一个套接字 */
    bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    /* 监听 */
    listen(sfd, 128);

    /* 等待（客户端）链接 */
    printf("waiting for connect...\n");
    addr_len = sizeof(client_addr);
    cfd = accept(sfd, (struct sockaddr *)&client_addr, &addr_len);

    cport = ntohs(client_addr.sin_port);
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));

    printf("client IP: %s\t%d\n", client_ip, cport);

    while ( 1 ) {
        /* 读取从客户端发送过来的数据 */
        len = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        for ( i=0; i<len; i++ ) {
            buf[i] = toupper(buf[i]);
        }

        /* 返回给客户端数据 */
        write(cfd, buf, len);
    }

    /* 关闭链接 */
    close(cfd);
    close(sfd);

    return 0;
}
