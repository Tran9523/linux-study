#include <stdio.h>
//12-1.c 문자열 상수가 주소란 증거 [문자 'a' - 'A' = 32]
int main(void)
{
    printf("apple이 저장된 시작 주소 값: %p\n", "apple");   // %p 16진수로 주소
    printf("두 번째 문자의 주소 값: %p\n", "apple" + 1);
    printf("첫 번째 문자: %c\n", *"apple");
    printf("두 번째 문자: %c\n", *("apple" + 1));
    printf("배열로 표현한 세 번째 문자: %c\n", "apple"[2]);

    return 0;
}