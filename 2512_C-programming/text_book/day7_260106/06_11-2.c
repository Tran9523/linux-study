#include <stdio.h>

//11-2.c 공백의 중요성
int main(void)
{
    char ch1, ch2;

    scanf(" %c %c", &ch1, &ch2);       // scanf 공백 넣고 테스트
    //scanf("%c%c", &ch1, &ch2);
    // 2개 문자 연속 입력
    printf("[%c%c]\n", ch1, ch2);
    printf("%d & %d\n", ch1, ch2);      // 아스키 코드 확인

    return 0;
}