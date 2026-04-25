#include <stdio.h>

//9-6.c
// *pd 값이 10이 될 수 있도록 수정 [pd를 int형 + %lf 에서 %d] [double a 선언]
int main(void)
{
    int a = 10;
    //double a = 10;
    int *p = &a;
    double *pd;

    pd = p;     //포인터 p 값을 포인터 pd에 대입
    
    printf("%lf\n", *pd);
    printf("%d\n", *p);
    
    return 0;
}