#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 8-6.c (gets 는 잘 안 쓰는 추세) - fgets(str, 100 = sizeof(str), stdin) 형식으로
int main(void)
{
    char str[80];

    printf("문자열 입력: ");
    scanf("%s", str);
    // Love is belief... 입력해도 Love 만 (개행문자 저장X & (공백)Love 동일)
    // gets(str); // 메모리랑 상관없이 입력됨(overflow)
    puts("입력된 문자열: ");
    puts(str);

    return 0;
}