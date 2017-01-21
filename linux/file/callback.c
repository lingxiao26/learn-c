#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void compareNum(int *ap, int cNum, int len, int (*p)(int, int))
{
    int i = 0;
    for ( i=0; i<len; i++ ) {
        if ( p(ap[i], cNum) ) {
            printf("ap[%d]: %d\n", i, ap[i]);
        }
    }
}

int gtCompareNum(int a, int cNum)
{
    return a > cNum;
}

int ltCompareNum(int a, int cNum)
{
    return a < cNum;
}

int main(void)
{
    int arr[5] = {20,43,55,70,23};
    int num = 50;
    int len = sizeof(arr)/sizeof(arr[0]);
    compareNum(arr, num, len, ltCompareNum);

    return 0;
}
