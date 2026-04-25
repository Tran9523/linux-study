#include <stdio.h>

// NULL까지 보고 싶음 -> 컴파일러가 알아서 끊어주는 느낌
int main(void)
{
    char str[9] = "Be happy!";

    printf("%s", str);

    return 0;
}