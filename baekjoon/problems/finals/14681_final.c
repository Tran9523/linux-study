#include <stdio.h>

int main(void)
{
    int a, b, i;

    scanf("%d %d", &a, &b);

    if (a > 0) {
        if (b > 0) {
            i = 1;
        } else {
            i = 4;
        }
    } else {
        if (b > 0) {
            i = 2;
        } else {
            i = 3;
        }
    }

    printf("%d\n", i);

    return 0;
}
