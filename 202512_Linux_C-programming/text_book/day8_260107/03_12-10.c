#include <stdio.h>
#include <string.h>
//12-10.c

int main(void)
{
    char str[80] = "straw";
    printf("후단까지 체크해보기: %d\n", str[6]);
    strcat(str, "berry");       // 널부터 데이터 붙임
    printf("%s\n", str);
    strncat(str, "piece", 3);
    printf("%s\n", str);

    return 0;
}