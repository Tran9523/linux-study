#include <stdio.h>
//13-2.c
int main(void)
{
    int a = 10, b = 20;

    printf("교환 전 a & b : %d, %d\n", a, b);
    {
        int temp;
        //int a, b;           // 같은 이름의 변수가 둘 이상이면 가까운 변수 사용

        temp = a;
        a = b;
        b = temp;
    }                           // 이 괄호닫음으로 temp는 사라짐
    printf("교환 후 a & b : %d, %d\n", a, b);

    return 0;
}