#include <stdio.h>

// 13-6.c
void add_ten(int a);     // void를 int로 바꿔도 동일

int main(void)
{
    int a = 10;

    add_ten(a);
    printf("a: %d\n", a);

    return 0;
}

void add_ten(int a)     // main에 있는 a를 복사해서 이 함수에 a를 만듬
{
    a += 10;
}