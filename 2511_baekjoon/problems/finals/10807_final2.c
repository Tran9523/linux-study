//배열 선언
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int N, cnt = 0, data;
    int ary[100];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &ary[i]);
    }
    scanf("%d", &data);
    for (int i = 0; i < N; i++) {
        if (data == ary[i]) cnt++;
    }
    printf("%d", cnt);

    return 0;
}
