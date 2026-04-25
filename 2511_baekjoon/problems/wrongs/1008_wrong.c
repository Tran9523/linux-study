// 1st : 백준은 허용치않은 입력이나 출력을 원하지 않음
#include <stdio.h>

int main(void)
{
    double a, b;

    printf("두 실수를 입력하세요: ");
    scanf("%lf%lf", &a, &b);
    if (a >= 10 || a <= 0 || b >= 10 || b <= 0) {
        printf("입력 오류");
        return 1;
    }

    printf("%lf", (a / b));

    return 0;
}

// 2nd : 실수 출력 lf은 기본 6~8자리라 백준이 요구한 10자리까지 별도로 출력처리를 해줘야 됨
#include <stdio.h>

int main(void)
{
    double a, b;

    scanf("%lf%lf", &a, &b);
    if (a >= 10 || a <= 0 || b >= 10 || b <= 0) {
        printf("입력 오류");
        return 1;
    }

    printf("%lf", (a / b));

    return 0;
}