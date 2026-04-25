#include <stdio.h>

//15-9.c void포인터는 간접 참조 연산과 주소에 대한 정수 연산이 불가능
int main(void)
{
    int a = 10;
    double b = 3.5;
    void *vp;       // 앞에 어떤 형태가 올건지 쓸때마다 알려줘야 됨

    vp = &a;
    printf("a: %d\n", *(int *)vp);

    vp = &b;
    printf("b: %.1lf\n", *(double *)vp);

    return 0;
}
//  a: 10
//  b: 3.5