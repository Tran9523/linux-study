#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int T;
    if (scanf("%d", &T) != 1) return 0;

    // 각 줄 최대: "2000\n" (A,B<=1000) => 5자 정도
    // 여유 있게 줄당 12자 잡으면 충분
    size_t cap = (size_t)T * 12 + 1;
    char *out = (char *)malloc(cap);
    if (!out) return 1;

    size_t pos = 0;

    for (int i = 0; i < T; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        // out+pos에 결과를 이어 붙임
        pos += (size_t)sprintf(out + pos, "%d\n", a + b);
    }

    fputs(out, stdout);
    free(out);
    return 0;
}

/*  N이 점점 작아지면서 자연스럽게 끝나는 구조 (속도랑 별개라 정확한 답은 아님)
int main(void)
{
    int N, a, b;
    scanf("%d", &N);
    while (N--) {
        scanf("%d %d", &a, &b);
        printf("%d\n", a + b);
    }
    return 0;
}
*/