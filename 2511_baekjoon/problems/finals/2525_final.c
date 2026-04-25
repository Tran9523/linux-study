#include <stdio.h>

int main(void)
{
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    b += c;

    a += (b / 60);
    if ( a >= 24) a -= 24;
    b = (b % 60);


    printf("%d %d", a, b);
    return 0;
}