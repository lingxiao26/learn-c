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
    int sfd;
    int len;
    char buf[1024];
    struct sockaddr_in serv_addr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));       /* 清空serv_addr结构体 */
    /* 初始化需连接的服务端的地址和端口 */
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.0.10", &serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(SERV_PORT);

    /* 连接 */
    connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    /* 从标准输入接受数据并发送到服务端，然后接受服务端返回的数据并打印到标准输出 */
    while ( (len = read(STDIN_FILENO, buf, sizeof(buf))) ) {
        write(sfd, buf, len);
        len = read(sfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
    }

    return 0;
}
