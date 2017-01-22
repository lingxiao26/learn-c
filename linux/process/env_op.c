#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
    int i;

    for ( i=0; environ[i]!=NULL; i++ ) {
        printf("%s\n", environ[i]);
    }
    printf("----------------------------------\n");

    /* 获取环境变量 */
    printf("PWD: %s\n", getenv("PWD"));

    /* 设置环境变量, 注意，此时设置的环境变量只在当前进程中有效 */
    setenv("PWD", "haha", 1);
    printf("PWD: %s\n", getenv("PWD"));

    return 0;
}
