#include <stdio.h>
#include <math.h>

// 실행할때 Ctrl+Alt+'N' 이 아니라 terminal에서 "gcc day3.c -o day3 S-lm" 입력
// 수학 기호 사용이라 <math.h> 가져와야 됨
int main(void)
{
    double x, y;

    printf("실수 x 입력: ");
    if (scanf("%lf", &x) != 1) return 1;
    printf("실수 y 입력 : ");
    if (scanf("%lf", &y) != 1) return 1;

    printf("\n [math.h 함수 예제]\n");
    printf("sqrt(x) = %.4f\n", sqrt(x));
    printf("pow(x, y) = %.4f\n", pow(x, y));
    printf("sin(x) = %.4f\n", sin(x));
    printf("cos(x) = %.4f\n", cos(x));
    printf("log(x) = %.4f\n", log(x));
    printf("fabs(x) = %.4f\n", fabs(x));

    return 0;
}