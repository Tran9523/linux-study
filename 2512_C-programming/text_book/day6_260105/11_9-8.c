#include <stdio.h>

//9-8.c (단 수정할 때 포인터를 쓰면 안됨)
void swap(void);
void swap_ary(int ary[]);    //2안 배열을 만들어서 진행 가능
int a = 10, b = 20;     //실제 스왑이 가능하려면 2 함수가 같은 변수를 사용해야...

int main(void)
{
    swap();
    int ary[2] = {10, 20};    //[2]안의 값이 2개라는 소리니까 개수 이해 잘하기
    swap_ary(ary);
    printf("a: %d, b: %d\n", a, b);
    printf("a: %d, b: %d -배열\n", ary[0], ary[1]);

    return 0;
}

void swap(void)
{
    int temp;

    temp = a;
    a = b;
    b = temp;
}

void swap_ary(int ary[])
{
    int temp;

    temp = ary[0];
    ary[0] = ary[1];
    ary[1] = temp;
}