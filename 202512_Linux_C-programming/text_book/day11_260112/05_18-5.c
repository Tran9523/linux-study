//18-5.c    사용하는 함수만 getchar 에서 fgetc, fputc로 변경
#include <stdio.h>

int main(void)
{
    int ch;

    while (1) {
        ch = fgetc(stdin);
        if (ch == EOF) break;
        fputc(ch, stdout);
    }

    return 0;
}