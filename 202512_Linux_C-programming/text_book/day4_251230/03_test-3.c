#include <stdio.h>

// 구구단 출력
int main(void)
{
    int i, j;
    int temp;

    for ( i = 1 ; i < 9; i++) {
        printf("%d단:", (i+1));
        for ( j = 0; j < 9; j++) {
            temp = (i + 1) * (j + 1);
            printf("%3d", temp);
        }
        printf("\n");
    }
    return 0;
}

// 6-3.c
int main(void)
{
    int a = 1;
    
    do
    {
        a *= 2;
    } while (a < 10);
    printf("a : %d\n", a);

    return 0;    
}       // a : 16