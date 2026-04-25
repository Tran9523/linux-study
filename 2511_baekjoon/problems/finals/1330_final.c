#include <stdio.h>

int main(void)
{
    int a, b;
    int res;

    scanf("%d %d", &a, &b);

    res = (a - b);

    if (res > 0) {
        printf(">");
    } else if (res < 0) {
        printf("<");
    } else {
        printf("==");
    }

    return 0;
}