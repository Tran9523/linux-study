#include <stdio.h>
#include <stdlib.h>
//연습문제 5 이건 메모리 관련이라 절대 실행 X
//정답을 굳이 찾자면 (ptr - 5) 가 맞지만, 그래도 원래 주소를 저장하는게 베스트

int main(void)
{
    int *ptr = (int *)malloc(sizeof(int) * 5);

    for (int i = 0; i < 5; i++) {
        *ptr = i * 10;
        ptr++;
    }

    free("");
    return 0;
}