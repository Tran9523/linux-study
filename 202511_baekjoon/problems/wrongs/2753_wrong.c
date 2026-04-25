//조건이 너무 난잡해져서 특정 상황에서 출력이 2번 됨
#include <stdio.h>

int main(void)
{
    int y;

    scanf("%d", &y);

    if ((y % 4) == 0) {
        if ((y % 100) == 0) {
            if ((y % 400) == 0) {
                printf("1");
            }
            printf("0");
        } else {
            printf("1");
        }
    } else {
        printf("0");
    }

    return 0;
}