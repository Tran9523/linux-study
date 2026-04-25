//언제나 조건 확인 이번에도 제대로 못 읽어서 실패
#include <stdio.h>

int main(void)
{
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    printf("%d\n",(a+b)%c);
    printf("%d\n",(a%c)+(b%c));
    printf("%d\n",(a*b)%c);
    printf("%d\n",((a%c)*(b%c))%c);
    return 0;
}