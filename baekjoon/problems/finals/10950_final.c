#include <stdio.h>

int main(void)
{
    int N, i;
    int a, b;

    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d%d", &a, &b);
        printf("%d\n", (a + b));
    }

    return 0;
}