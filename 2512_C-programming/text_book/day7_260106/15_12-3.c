#include <stdio.h>

//12-3.c 버퍼 찌꺼기
int main(void)
{
    char str[80];

    printf("문자열 입력: ");
    scanf("%s", str);       // apple jam 교재 추천
    printf("첫 번째 단어: %s\n", str);
    scanf("%s", str);       // 추가 입력 없이 남는걸로 들어감(공백 없어야 2번)
    printf("버퍼에 남아 있는 두 번째 단어: %s\n", str);

    return 0;
}