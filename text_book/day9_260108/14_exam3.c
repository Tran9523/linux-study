#include <stdio.h>
//연습문제 3 - 후위니까 10 맞지
int main(void)
{
    int arr[] = {10, 20, 30};
    int *ptr = arr;

    printf("%d", *ptr++);
    return 0;
}