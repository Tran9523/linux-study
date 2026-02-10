#include <stdio.h>

int main(void)
{
    long long X;
    int N, a, b;
    long long x = 0;

    scanf("%lld", &X);
    scanf("%d", &N);
    
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &a, &b);
        x += (a * b);
    }

    if (X == x) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}
