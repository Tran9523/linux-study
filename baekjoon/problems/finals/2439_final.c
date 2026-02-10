#include <stdio.h>

int main(void)
{
    int N;
    int i, j;

    scanf("%d", &N);
    for (i = 1; i < N + 1; i++) {
        for (j = 0; j < N - i; j++){
            printf(" ");
        }
        for (j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
