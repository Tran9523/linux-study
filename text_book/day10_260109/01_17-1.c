#include <stdio.h>

//17-1.c 구조체는 포인터 만큼이나 많이 씀 (현업에서는 포인터랑 배열만 잘 써도 뽑겟다 마인드)
//구조체 배울때 붕어빵 틀 이라고도 표현 (대신 이건 제일 긴 기준으로 배정 + 패딩바이트 생각)
struct student {
    int num;
    double grade;
};          // 구조체 예약은 밖에서 선언

int main(void)
{
    struct student s1;      // 얘는 붕어빵

    s1.num = 2;             // . 접근 연산자
    s1.grade = 2.7;
    printf("학번: %d\n", s1.num);
    printf("학점: %.1lf\n", s1.grade);

    return 0;
}