#include <stdio.h>

int main(void)
{
    int N;
    int sum = 0;

    scanf("%d", &N);

    for(int i = 1; i < N+1; i++) {
        sum += i;
    }
    printf("%d\n", sum);

    return 0;
}
