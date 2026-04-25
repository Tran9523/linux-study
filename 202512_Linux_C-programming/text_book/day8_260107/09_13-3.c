#include <stdio.h>
//13-3.c
void assign10(void);
void assign20(void);

int a;          // 전역으로 지정, 전역 변수는 알아서 0으로 초기화 해줌

int main(void)
{
    printf("Before 'A': %d\n", a);

    assign10();
    assign20();

    printf("After 'A': %d\n", a);
    
    return 0;
}

void assign10(void)
{
    a = 10;
}

void assign20(void)
{
    int a;   // 이렇게 선언하면 이거 우선 사용

    a = 20;
}