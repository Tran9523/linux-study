#include <stdio.h>

//17-10.c - 공용체(union) = 큰거 기준으로 하나만 전달
//전체 8바이트를 4 & 8이 나눠서 사용 [구조체 였다면 16바이트]
union student {
    int num;
    double grade;
};

int main(void)
{
    union student s1 = {315};

    printf("학번: %d\n", s1.num);
    s1.grade = 4.4;
    printf("학점: %.1lf\n", s1.grade);
    printf("학번: %d\n", s1.num);
    
    return 0;
}