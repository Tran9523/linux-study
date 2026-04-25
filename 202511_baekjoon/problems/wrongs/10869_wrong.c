// a, b의 형태를 제대로 못하고 있음 쭉 int로 해도 어차피 나누기 됐을거임
#include <stdio.h>

int main(void)
{
    double a, b;

    scanf("%d%d", &a, &b);
    if (a > 10000 || a <= 0 || b > 10000 || b <= 0) {
        printf("입력 오류");
        return 1;
    }

    printf("%d\n%d\n%d\n%lf\n%d", (a+b), (a-b), (a*b), (a/b), (a % b));

    return 0;
}