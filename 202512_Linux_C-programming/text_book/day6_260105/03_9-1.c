#include <stdio.h>

//9-1.c 주소 값 확인
int main(void)
{
    int a;
    double b;
    char c;

    printf("int address : %u\n", &a);       // 주소 연산자 %u
    printf("double address : %u\n", &b);
    printf("char address : %u\n", &c);

    return 0;
    //  int address : 1540405340 -> 할때마다 달라짐
    //  double address : 1540405344
    //  char address : 1540405339
}