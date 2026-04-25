#include <stdio.h>

// 4-8 변수형 테스트
int main(void)
{
    int a = 20, b = 3;
    double res;
    double c = 551530.109;

    res = ( (double)a ) / ( (double)b );
    printf("a = %d, b = %d\n", a, b);
    printf("a / b 의 결과 : %d\n", (a / b));
    printf("a / b 의 결과 : %.10lf\n", res);

    a = (int)res;
    printf("(int) %.1lf의 결과 : %d\n", res, a);
    printf("%5.2lf\n", c);

    return 0;
}