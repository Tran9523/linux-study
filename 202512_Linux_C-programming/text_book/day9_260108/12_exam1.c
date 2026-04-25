#include <stdio.h>
//연습문제 1 (48이라 씀 -> 비트 연산 방향 헷갈림)
int main(void)
{
    unsigned char b = 12;
    printf("%d", b >> 2);

    return 0;
}