#include <stdio.h>
//교수님 실험 문제 - 3 / 4 / 5 / 3 / 7
// static 정적 변수의 초기화는 프로그램 시작 시 단 한 번 ( = 이라고 다 들어가는게 아님)
void fA(void)
{
    static int x = 1;
    x += 2;
    printf("A = %d\n", x);
}
void fB(void)
{
    static int x = 5;
    x -= 1;
    printf("B = %d\n", x);
}

int main(void)
{
    fA();
    fB();
    fA();
    fB();
    fA();

    return 0;
}