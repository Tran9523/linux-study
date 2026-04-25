#include <stdio.h>
//13-5.c 컴파일러가 알아서 레지스터 넣어줌 (양이 많으면) - 10만이나 100만이나 비슷
//register = 0.059 seconds
//int i = 0.06 seconds 
int main(void)
{
    register int i;
    auto int sum = 0;

    for (i = 1; i < 1000000; i++) {
        sum += i;
    }

    printf("%d\n", sum);

    return 0;
}