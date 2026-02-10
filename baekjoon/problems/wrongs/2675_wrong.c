//삼중 for문 구조도 틀렸고 원하는 문자가 최대 20개여서 칸 수도 늘리고 전체를 돌려버리면 오류가 나서 널을 기다려야
#include <stdio.h>

int main(void)
{
    int N, n, i, j, k;
    char a[8];

    scanf("%d", &N);
    scanf("%d %s", &n, a);
    for (i = 0; i < N; i++) {
        for (j = 0; j < 8; j++) {
            for (k = 0; k < n; k++) {
                printf("%c", a[i]);
            }
        }
        printf("\n");
    }

    return 0;
}