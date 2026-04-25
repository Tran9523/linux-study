#include <stdio.h>

//13-7.c
void add_ten(int *pa);

int main(void)
{
    int a = 10;

    add_ten(&a);
    printf("a = %d\n", a);

    return 0;
}

void add_ten(int *pa)
{
    *pa += 10;
}