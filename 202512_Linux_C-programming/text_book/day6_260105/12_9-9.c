#include <stdio.h>

//9-9.c 단순 변수는 공유되지 않는다. 증명
void swap(int x, int y);

int main(void)
{
    int a = 10, b = 20;

    swap(a, b);
    printf("a: %d, b: %d\n", a, b);

    return 0;
}

void swap(int x, int y)
{
    int temp;

    temp = x;
    x = y;
    y = temp;
}