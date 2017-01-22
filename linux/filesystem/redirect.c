#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int redirect(char *filename, int dst_fd /* 重定向的目标文件描述符 */)
{
    struct stat sb;
    int ret = 0;
    char buf[1024];
    /* 判断文件是否为普通文件 */
    ret = stat(filename, &sb);
    if ( ret == -1 ) {
        perror("stat error: ");
        exit(1);
    }
    if ( (sb.st_mode & S_IFMT) != S_IFREG ) {
        fprintf(stderr, "%s not a regular file!\n", filename);
        exit(1);
    }
    int fd = open(filename, O_RDONLY);
    if ( fd == -1 ) {
        perror("open error: ");
        exit(1);
    }
    while ( (ret=read(fd, buf, sizeof(buf))) != 0 ) {
        write(dst_fd, buf, ret);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int dst_fd = STDOUT_FILENO;
    if ( argc != 2 && argc != 4 ) {
        fprintf(stderr, "Usage: %s SRC [ > DST ]\n", __FILE__);
        exit(1);
    }
    if ( argc == 4 ) {
        if ( argv[2] != ">" ) {
            fprintf(stderr, "Usage: %s SRC [ > DST ]\n", __FILE__);
            exit(1);
        }
        dst_fd = open(argv[3], O_WRONLY | O_CREAT, 0664);
        if( dup2(dst_fd, STDOUT_FILENO) == -1 ) {
            perror("dup2 error: ");
            exit(1);
        } 
    }
    redirect(argv[1], dst_fd);

    return 0;
}
