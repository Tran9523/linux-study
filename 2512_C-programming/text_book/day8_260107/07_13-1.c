#include <stdio.h>
//13-1.c 매개변수 void 에서 a로 변경해도 동일
void assign(int a);
int main(void)
{
    auto int a = 0; // 자동 지정인데 안 씀

    assign(a);
    printf("main함수 a: %d\n", a);

    return 0;
}

void assign(int a)
{
    //int a;

    a = 10;
    printf("assign함수 a: %d\n", a);
}
