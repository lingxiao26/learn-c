#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _teacher {
    int id;
    char *name;
} teacher_t;

void print_teacher(teacher_t *pt)
{
    printf("id: %d  name: %s\n", pt->id, pt->name);
}

int main(void)
{
    teacher_t t1, t2;
    t1.id = 1;
    t1.name = (char *)malloc(sizeof(char)*64);
    memset(t1.name, 0, 64);
    strcpy(t1.name, "xiao");
    print_teacher(&t1);

    t2 = t1;
    print_teacher(&t2);

    if ( t1.name != NULL ) {
        free(t1.name);
        t1.name = NULL;
    }
    /* 通过直接赋值来拷贝，如果结构体里面有指针，复制之后的结构体和原结构体指针变量的成员会指向 \
     * 同一块内存地址，如果重复释放内存会导致程序崩溃
    if ( t2.name != NULL ) {
        free(t2.name);
        t2.name = NULL;
    }
    */

    return 0;
}
