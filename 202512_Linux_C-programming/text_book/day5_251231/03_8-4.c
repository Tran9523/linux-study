#include <stdio.h>

// 8-4.c 문자열 덮어쓰기 이후
int main(void)
{
    char str[80] = "applejam";  // 초기화 하지 않은 경우 쓰레기 들어감
    //char str[80] = { 'a', 'p','p'};  // 뒤에 널 문자 붙는지 확인용

    printf("최초 문자열: %s\n", str);
    printf("문자열 입력: ");
    scanf("%s", str);  // 문자열은 & 입력X - 남은 문자열은 덮어쓰기라 남아있음
    printf("입력 후 문자열: %s\n", str);
    printf("입력 후 9번째 문자 & ASCII 문자: %c, %d\n", str[8], str[8]);    // str[] = "grape \0 am \0" 인 상태

    return 0;
}