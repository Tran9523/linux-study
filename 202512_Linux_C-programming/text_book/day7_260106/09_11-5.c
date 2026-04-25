#include <stdio.h>
//11-5.c 반복문 통해 버퍼 다 내기
int main(void)
{
    int res;
    char ch;
    
    while (1) {     // 무한반복문
        res = scanf("%c", &ch);
        if (res == -1) break;
        printf("%d ", ch);
    }
}