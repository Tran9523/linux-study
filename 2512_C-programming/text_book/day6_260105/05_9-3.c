#include <stdio.h>

//9-3.c 포인터로 숫자 넣어보기
int main(void)
{
    int a = 10, b = 15, total;
    double avg;
    int *pa, *pb;    // double 로 실행 시 -523383048, 0 등으로 오류
    int *pt = &total;
    double *pg = &avg;

    pa = &a;
    pb = &b;
    *pt = *pa + *pb;
    *pg = *pt / 2.0;

    //*pa = 20;
    //b = 40;

    printf("두 정수의 값: %d, %d\n", *pa, *pb);
    printf("두 정수의 합: %d\n", *pt);
    printf("두 정수의 평균: %.1lf\n", *pg);
    printf("두 정수의 값: %d, %d\n", a, b);
    printf("두 정수의 합: %d\n", total);
    printf("두 정수의 평균: %.1lf\n", avg);

    return 0;
}