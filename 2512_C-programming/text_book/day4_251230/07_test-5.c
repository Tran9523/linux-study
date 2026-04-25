#include <stdio.h>

// test 두 수 의 평균을 구하는 코드 - main & avg
double avg(int x, int y);

int main(void)
{
    int a, b;

    printf("두 수를 입력하세요: ");
    scanf("%d %d", &a, &b);

    printf("두 수의 평균은 %.1lf 입니다.\n", avg(a,b));

    return 0;
}

double avg(int x, int y)
{
    double res;

    res = (x + y) / 2.0;
    return res;
}