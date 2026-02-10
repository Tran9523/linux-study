#include <stdio.h>

int main(void)
{
    int N, x, i, a;

    scanf("%d %d", &N, &x);

    for (i = 0; i < N; i++) {
        scanf("%d", &a);
        if (a < x) printf("%d\n", a);
    }

    return 0;
}
