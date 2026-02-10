//동적할당 (뭐든 대처 가능)
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int N, cnt = 0, data;
    scanf("%d", &N);
    int *pi = malloc(sizeof(int) * N);
    if (pi == NULL) {
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &pi[i]);
    }
    scanf("%d", &data);
    for (int i = 0; i < N; i++) {
        if (data == pi[i]) cnt++;
    }
    printf("%d", cnt);

    free(pi);
    return 0;
}
//int *tmp = (int *) realloc(pi, sizeof(int) * size);
//if (!tmp) { free(pi); return 1;}
//pi = tmp;