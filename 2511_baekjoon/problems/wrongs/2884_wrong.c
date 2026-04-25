//계산 다 해놓고 출력이 없어서 fail
#include <stdio.h>

int main(void)
{
    int a, b;
    int res;

    scanf("%d %d", &a, &b);

    b -= 45;

    if (b < 0) {
        a -= 1;
        b += 60;
    }
    if (a < 0) {
        a = 23;
    }

    return 0;
}