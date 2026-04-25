#include <stdio.h>

//13-4.c
void auto_func(void);
void static_func(void);

//int a;    이렇게 선언해도 동일
int main(void)
{
    int i;
    //static int a;     //이렇게 선언하면 static_func으로 안 날라감

    printf("일반 지역 변수(auto)를 사용한 함수...\n");
    for (i = 0; i < 3; i++) {
        auto_func();
    }

    printf("정적 지역 변수(static)를 사용한 함수...\n");
    for (i = 0; i < 3; i++) {
        static_func();
    }

    return 0;
}

void auto_func(void)
{
    auto int a = 0;
    a++;
    printf("%d\n", a);
}

void static_func(void)
{
    static int a;           // 정적 변수라 0으로 초기화
    a++;
    printf("%d\n", a);
}