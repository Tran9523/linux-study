#include <stdio.h>

int main(void)
{
    int N, n, i, j, k;
    char a[21];

    scanf("%d", &N);

    for (i = 0; i < N; i++) {
        scanf("%d %s", &n, a);

        for (j = 0; a[j] != '\0'; j++) {
            for (k = 0; k < n; k++) {
                putchar(a[j]);
            }
        }
        putchar('\n');
    }
    return 0;
}
