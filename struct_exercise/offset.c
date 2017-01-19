#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _teacher {
    int id;
    char name[64];
    int age;
} teacher_t;

int main(void)
{
    int id_pos = (int)&(((teacher_t *)0)->id);
    int name_pos = (int)&(((teacher_t *)0)->name);
    int age_pos = (int)&(((teacher_t *)0)->age);

    printf("id_pos: %d\nname_pos: %d\nage_pos: %d\n", id_pos, name_pos, age_pos);
    /* -------------------- result --------------------- */
    /* id_pos:   0   === 0 ------------------------------*/
    /* name_pos: 4   === sizeof(id_pos) -----------------*/
    /* age_pos:  68  === sizeof(id_pos)+sizeof(name_pos) */
    
    return 0;
}
