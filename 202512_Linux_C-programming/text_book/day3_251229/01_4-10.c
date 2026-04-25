#include <stdio.h>

// 예제 4-10.c 복합 연산자 확인
int main(void)
{
    int a = 10, b= 20;
    int res = 2;

    a += 20;
    res *= b + 10;

    printf("a = %d, b = %d\n", a, b);
    printf("res = %d\n", res);

    return 0;
}