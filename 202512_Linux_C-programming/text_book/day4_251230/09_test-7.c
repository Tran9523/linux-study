#include <stdio.h>
// for문으로 값 넣기
int get_num(void);

int main(void)
{
    int i;
    int result[10];

    for (i = 0; i < 10; i++) {
        result[i] = get_num();
    }

    for (i = 0; i < 10; i++) {
        printf("%d번째 반환값 : %d\n", i + 1, result[i]);
    }
    return 0;
}

int get_num(void)
{
    int num;

    printf("양수 입력: ");
    scanf("%d", &num);

    return num;
}