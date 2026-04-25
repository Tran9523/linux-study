#include <stdio.h>
//9-7.c
//함수를 벗어나면 같은 변수가 아님 다르게 적용 = 그래서 포인터를 넣어야 변환 가능
void swap(int *pa, int *pb);    // 포인터로 swap
void swap2(int a, int b);       // 변수로 직접 swap

int main(void)
{
    int a = 10, b = 20;

    swap2(a, b);
    printf("a:%d, b:%d\n", a, b);   // 변수가 각각 다르기에 10 20 유지됨

    swap(&a, &b);
    printf("a:%d, b:%d\n", a, b);

    return 0;
}

void swap(int *pa, int *pb)
{
    int temp;

    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void swap2(int a, int b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;

    return;     // 던져줄 값이 2개라 식을 다르게 적어야됨
}