#include <stdio.h>
#include <stdlib.h>

/* 结构体字节对齐 */
/* 字节对齐的方法 */
/* 1. 结构体的首地址要能被对齐基数整除*/
/* 2. 将结构体成员中最宽的数据类型作为结构体字节对齐的基数 */
/* 3. 每个成员必须放在能够整除自己大小的地址上 */

typedef struct _student {
    char c;
    double d;
    short s;
    int i;
} student_t;

int main(void)
{
    student_t s1;
    printf("len s1: %d\n", sizeof(s1)); 
    /* result: 24 */

    return 0;
}
