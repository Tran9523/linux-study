//10^12 라 int로는 다 못 받음 (int는 10^9)
#include <stdio.h>

int main(void)
{
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    printf("%d", (a + b + c));
    return 0;
}