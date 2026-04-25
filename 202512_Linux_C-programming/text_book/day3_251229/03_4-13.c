#include <stdio.h>

// 4-13.c 비트연산자 테스트
int main(void)
{
    int a = 10; // 비트열 00000000 00000000 00000000 00001010
    int b = 12; // 비트열 00000000 00000000 00000000 00001100

    printf("a & b : %d\n", a & b);
    printf("a ^ b : %d\n", a ^ b);
    printf("a | b : %d\n", a | b);
    printf("~a : %d\n", ~a);
    printf("a << 1 : %d\n", a << 1);        // 앞의 0은 버려지고 뒤에는 0으로 채워짐
    printf("a >> 2 : %d\n", a >> 2);        // 8421 이라는 코드 (사실상 2진수)

    return 0;
}