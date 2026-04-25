#include <stdio.h>
// degree(각도) 와 radian(파이)을 변환하는 함수
#define PI 3.141592
double change(int, double);

int main(void)
{
    int a;
    double b;
    double result;

    printf("1. Degree -> Radian\n");
    printf("2. Radian -> Degree\n");
    printf("변환할 형식과 변환할 값을 입력하세요.");
    if (scanf("%d %lf", &a, &b) != 2) {
        printf("입력 형식이 올바르지 않습니다.\n");
        return 1;
    }

    result = change(a, b);

    if(a == 1) {
        printf("%.2lf Degree -> %.2lf Radian\n", b, result);
    } else if (a == 2) {
        printf("%.2lf Radian -> %.2lf Degree\n", b, result);
    } else {
        printf("변환 값을 잘못 입력하였습니다.\n");
        return 1;
    }
    
    return 0;
}

double change(int a, double b)
{
    switch(a) {
        case 1: return b * PI / 180.0;
        case 2: return b * 180.0 / PI;
    }

    return 0.0;
}