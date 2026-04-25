//배열 구조를 완전히 무시하고 짠거라 절대 맞을 수가 없는 구조
//차라리 체크 배열로 입력 받고 나서 cnt를 늘리는 구조
#include <stdio.h>

int main(void)
{
    int N = 30;
    int ary[30];
    int a, x, y;

    for (int i = 0; i < 30; i++) {
        ary[i] = (i + 1);
    }
    for (int i = 0; i < 28; i++) {
        scanf("%d", &a);
        if (ary == a) ary = 0;
    }

    if (ary != 0) x = ary[i];
    if (ary != 0) y = ary[i];

    printf("%d\n%d", x, y);

    return 0;
}