#include <stdio.h>
//14-3.c 2차원 배열 초기화
int main(void)
{
    char animal[5][20];
    int i;
    int count;

    printf("animal[0]의 사이즈 = %ld\n", sizeof(animal[0])); // 2차원에서 행만 쓰면 열 자동
    //printf("animal[][0]의 사이즈 = %d\n", sizeof(animal[][0])); // 2차원에서 행만 쓰면 열 자동
    //행은 생략불가 표현, 차라리 sizeof(animal[0]) / sizeof(animal[0][0]); 으로 구하기
    printf("animal[0][0]의 사이즈 = %ld\n", sizeof(animal[0][0])); // 2차원에서 행만 쓰면 열 자동
    count = sizeof(animal) / sizeof(animal[0]);     // 이게 젤 중요한 포인트 - 100 / 20
    for (i = 0; i < count; i++) {
        scanf("%s", animal[i]);
    }
    for (i = 0; i < count; i++) {
        printf("%s\t", animal[i]);
    }
    printf("\n");

    return 0;
}