//18-4.c    버퍼의 개념을 다시 생각할 수 있도록 반복
#include <stdio.h>

int main(void)
{
    int ch;

    while (1) {
        ch = getchar();
        if (ch == EOF) {break ;}
        putchar(ch);
    }

    return 0;
}