#include <stdio.h>

int main(void)
{
    int N;
    int x, min, max;

    scanf("%d", &N);
    scanf("%d", &x);
    min = max = x;

    for (int i = 1; i < N; i++) {
        scanf("%d", &x);
        if (x < min) min = x;
        if (x > max) max = x;
    }

    printf("%d %d\n", min, max);

    return 0;
}