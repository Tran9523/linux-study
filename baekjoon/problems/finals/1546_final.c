#include <stdio.h>

int main(void)
{
    int N, max = 0;
    int ary[1000];
    double avg = 0.0;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &ary[i]);
        if (max < ary[i]) max = ary[i];
    }

    for (int i = 0; i < N; i++) {
        avg += (double)ary[i] / max * 100.0; 
    }
    printf("%lf", (avg / N));
    
    return 0;
}
