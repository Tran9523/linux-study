#include <stdio.h>

// 7-1.c 함수 추가하기
int sum(int x, int y)
{
    int temp;

    temp = x + y;

    return temp;
}

int main(void)
{
    int a = 10, b = 20;
    int result;

    result = sum(a, b);
    printf("result : %d\n", result);

    return 0;
}