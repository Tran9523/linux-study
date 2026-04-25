#include <stdio.h>

int main(void)
{
    double a, b;

    scanf("%lf%lf", &a, &b);
    if (a >= 10 || a <= 0 || b >= 10 || b <= 0) {
        printf("입력 오류");
        return 1;
    }

    printf("%.10lf", (a / b));

    return 0;
}