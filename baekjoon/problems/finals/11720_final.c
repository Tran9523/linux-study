#include <stdio.h>

int main(void)
{
    int N, sum = 0;
    char ch;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf(" %c", &ch);
        sum += ch - '0';
    }
    printf("%d", sum);

    return 0;
}
