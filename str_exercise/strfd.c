#include <stdio.h>
#include <string.h>


int main(void)
{
    char *str1 = "89hello3829hellojifhellod939xhellosox98hello";
    char *str2 = "hello";
    char *p = NULL;
    p = str1;
    int cnt = 0;
/*
    do {
        p = strstr(p, str2);
        if ( p != NULL ) {
            cnt++;
            p++;
        }
    } while ( p != NULL );
    printf("cnt: %d\n", cnt);
*/
    p = strstr(p, str2);
    while ( p != NULL ) {
        cnt++;
        p++;
        p = strstr(p, str2);
    }

    printf("cnt: %d\n", cnt);

    return 0;
}
