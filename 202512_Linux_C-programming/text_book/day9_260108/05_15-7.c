#include <stdio.h>
//15-7.c 배열 포인터 = int (*pa)[4];
int sum(int, int);

int main(void)
{
    int (*fp)(int, int);        // 포인터 하나를 선언한게 끝
    int res;

    fp = sum;       // 함수형태를 받는 포인터 (그러면 뒷단이 받는 매개변수)
    res = fp(10, 20);
    printf("result: %d\n", res);

    return 0;
}
int sum(int a, int b)
{
    return (a + b);
}
//  result: 30