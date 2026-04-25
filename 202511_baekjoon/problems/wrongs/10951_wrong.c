//백준에서 원하는 무한 회귀 함수 형태가 아님. 애초에 무한 반복문은 되게 위험함
#include <stdio.h>

int main(void)
{
    int a, b;

    while (!0) {
        scanf("%d %d", &a, &b);
        printf("%d", (a+b));
    }

    return 0;
}
