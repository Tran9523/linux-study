#include <stdio.h>
#include <time.h>

// 랜덤 함수 써보기
int main(void)
{
    srand(time(NULL));  // 랜덤 초기화

    int r1 = rand() % 10; // 0~9사이
    int r2 = rand() % 100 + 1; // 0~99 에서 +1
    int r3 = rand() % 21 - 10; // 20이후 빼기니까 -10 ~ 10 사이
//    int num = rand();  // 0이상 RAND_MAX 이하의 정수 (32767-2bytes & 4bytes)

    printf("0~9 랜덤: %d\n", r1);
    printf("1~100 랜덤: %d\n", r2);
    printf("-10~10 랜덤: %d\n", r3);

    return 0;
}