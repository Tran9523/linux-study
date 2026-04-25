#include <stdio.h>

//test pa = "mango" 하고 3번째 문자를 m으로 바꾸기? -> 문자열 상수라 변경 불가
int main(void)
{
    char *pc = "mango";

    printf("%c\n", pc[2]);
    pc[2] = 'm';
    printf("%c\n", pc[2]);      // Segmentation fault (core dumped)
    
    return 0;
}