//한 글자씩 끊어읽는다를 배우지 않아서 해결 불가
#include <stdio.h>

int main(void)
{
    int N, ch, sum = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf(" %lc", &ch);
        sum += ch;
    }
    printf("%d", sum);

    return 0;
}
