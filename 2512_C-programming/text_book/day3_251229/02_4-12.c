#include <stdio.h>

// 예제 4-12.c 간단 if문
int main(void)
{
    int a = 40, b = 20, res;

    res = (a > b) ? a*2-b : a+b;
    printf("큰 값 : %d\n", res);

    return 0;
}