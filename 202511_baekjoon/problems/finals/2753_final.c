#include <stdio.h>

int main(void)
{
    int y;

    scanf("%d", &y);

    printf("%d\n", (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
    return 0;
}