#include <stdio.h>

//17-11.c 열거형(enum) = 코드를 눈으로 읽기 편하게
//뭔지 한번 더 물어보기 ( 0, 1, 2, 3 의 의미라고 함) = 의미를 코드에 남기기 위해
enum season {SPRING, SUMMER, FALL, WINTER};

int main(void)
{
    enum season ss;
    char *pc = NULL;

    ss = SPRING;
    
    switch (ss) {
        case SPRING:
            pc = "inline"; break;
        case SUMMER:
            pc = "swimming"; break;
        case FALL:
            pc = "trip"; break;
        case WINTER:
            pc = "skiing"; break;
    }
    printf("나의 레저 활동 => %s\n", pc);
}