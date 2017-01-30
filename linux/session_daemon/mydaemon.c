#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void mydaemon(void)
{
    pid_t pid, sid;
    /* 1. 创建子进程，父进程退出 */
    pid = fork();
    if ( pid == -1 ) {
        perror("fork error: ");
        exit(1);
    } else if ( pid > 0 ) {
        exit(1);
    }
    /* 2. 在子进程中创建新会话 */
    sid = setsid();
    if ( sid == -1 ) {
        perror("setsid error: ");
        exit(1);
    }
    /* 3. 改变当前目录为根目录 */
    int ret = chdir("/");
    if ( ret == -1 ) {
        perror("chdir error: ");
        exit(1);
    }
    /* 4. 重设文件权限掩码 */
    umask(0022);

    /* 5. 关闭文件描述符 */
    close(STDIN_FILENO);
    int fd = open("/dev/null", O_RDWR);
    if ( fd == -1 ) {
        perror("open error: ");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    return ;

}

int main(void)
{
    mydaemon();

    /* 6. 开始执行守护进程核心工作 */
    while ( 1 );

    return 0;
}
