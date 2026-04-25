#include <stdio.h>
// 11-1.c ASCII code
int main(void)
{
    char small, cap = 'G';

    if ((cap >= 'A') && (cap <= 'Z'))
    {
        small = cap + ('a' - 'A');
    }
    printf("대문지: %c %c", cap, '\n');     // 연습용이라 엔터를 %c로 받음
    printf("소문자: %c", small);

    return 0;
}