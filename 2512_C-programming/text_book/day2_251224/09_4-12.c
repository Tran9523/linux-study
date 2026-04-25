#include <stdio.h>

// 4-12.c 한줄짜리 if문
int main(void)
{
int a = 10, b = 20, res;

res = (a > b) ? a : b;
printf("큰 값 : %d\n", res);

return 0;
}