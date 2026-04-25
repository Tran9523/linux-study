#include <stdio.h>

//12-7.c put는 자동 줄바꿈 / fputs는 아님
int main(void)
{
    char str[80] = "apple juice";
    char *ps = "banana";

    puts(str);              // 출력 후 줄바꿈
    fputs(ps, stdout);
    puts("milk");

    return 0;
}