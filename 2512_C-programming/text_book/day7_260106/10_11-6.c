#include <stdio.h>

//11-6.c 입출력 용 별도의 함수
void my_gets(char *str, int size);

int main(void)
{
    char str[7];

    my_gets(str, sizeof(str));
    printf("입력한 문자열 %s\n", str);

    return 0;
}

void my_gets(char *str, int size)
{
    int ch;
    int i = 0;

    ch = getchar();     // 바로 엔터치면 프로그램 종료
    while ((ch != '\n') && (i < size -1))
    {
        str[i] = ch;
        i++;
        ch = getchar();
    }
    str[i] = '\0';          // NULL을 넣어야 안전하게 됨 + 끝을 알려줌
}