#include <stdio.h>
#include <stdlib.h>

//16-2.c - 주의 - pi로 주소 지정했다가 다른 주소로 덮어씌웠다? -> malloc 찾을 수 없어서 누수
int main(void)
{
    int *pi;
    int i, sum = 0;

    pi = (int *)malloc(5 * sizeof(int));    // 배열처럼 사용하겠다 - 이 형태 많이 씀
    if (pi == NULL) {
        printf("# 메모리가 부족합니다.\n");
        exit(1);
    }

    printf("다섯 명의 나이를 입력하세요: ");
    for (i = 0; i < 5; i++){
        scanf("%d", &pi[i]);
        sum += pi[i];
    }
    printf("다섯 명의 평균 나이: %.1lf\n", (sum / 5.0));
    free(pi);       // pi 주소를 놓쳐버리면 free로 할당된 영역 못 품

    return 0;
}