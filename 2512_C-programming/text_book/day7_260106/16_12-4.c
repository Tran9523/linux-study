#include <stdio.h>

//12-4.c     gets 는 개행문자 갖고오면 널로 바꿈(널+널 끝단)
int main(void)
{
    char str[80];

    printf("공백이 포함된 문자열 입력: ");
    gets(str);      // gets는 항상 오버플로우 조심
    printf("입력한 문자열: %s\n", str);    // 버퍼에서는 \n으로 끝 표시를 하지만
                                        // 배열에서는 \0을 붙임 - NUL 아스키코드0
    printf("끝 자리 확인: %c & %d\n", str[9], str[9]);
    return 0;
}