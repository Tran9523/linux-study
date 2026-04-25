#include <stdio.h>

//11-3.c 다른 입출력 코드
int main(void)
{
    int ch;

    ch = getchar();     // char만 받는걸로 정해져있어서 붙여써도 하나만 받음
    printf("입력한 문자: ");
    putchar(ch);        // 이건 출력하는거
    putchar('\n');      // get은 받는 위치가 앞으로, put은 뒤로 받음

    return 0;
}