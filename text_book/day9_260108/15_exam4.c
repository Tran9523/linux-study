#include <stdio.h>
//연습문제 4 5라 결과적으론 맞음 
int main(void)
{
    int arr[2][3] = { {1,2,3}, {4,5,6} };
    int (*p)[3] = arr;
    printf("%d", *(*(p + 1) + 1));

    return 0;
}