#include <stdio.h>

// test 문제 별 찍기
int main(void)
{
    int i, j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if( (i == j) || ( (i + j) == 4))
            {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}