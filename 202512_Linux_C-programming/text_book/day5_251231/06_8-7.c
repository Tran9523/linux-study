#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 8-7.c fgets(str, 100 = sizeof(str), stdin) 형식으로 실제 사용
int main(void)
{
    char str[80];

    printf("%s\n", str);

    str[0] = 'O';
    str[1] = 'K';
    fgets(str, sizeof(str), stdin);     // fgets 사용
    printf("%s\n", str);

    return 0;
}