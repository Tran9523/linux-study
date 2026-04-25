#include <stdio.h>

//10-2.c 포인터를 배열명처럼 사용하기
int main(void)
{
    int ary[3];
    int *pa = ary;
    int i;

    *pa = 10;
    *(pa + 1) = 20;
    pa[2] = pa[0] + pa[1]; // ary = &ary[0] / ary[0] = pa[0]

    for (i = 0; i < 3; i++) 
    printf("%5d", ary[i]);

    return 0;
}