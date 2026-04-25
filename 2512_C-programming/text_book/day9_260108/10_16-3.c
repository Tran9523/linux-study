#include <stdio.h>
#include <stdlib.h>
//16-3.c
int main(void)
{
    int *pi;
    int size = 5;
    int count = 0;
    int num;
    int i;

    pi = (int *)calloc(size, sizeof(int));      // size개 들어갈 공간 만들기
                                //size랑 sizeof랑 혼란 X
    while (1) {
        printf("양수만 입력하세요 => ");
        scanf("%d", &num);
        if (num <= 0) break;
        if (count == size) {
            size += 5;
            pi = (int *)realloc(pi, size * sizeof(int));    // realloc 할당 오류 주의
        }                       // 할당 과정에서 주소가 바뀐다고 해도 상관 없이 pi가 따라감
        pi[count++] = num;
    }
    for (i = 0; i < count; i++) {
        printf("%5d", pi[i]);
    }
    free(pi);

    return 0;
}