#include <stdio.h>

//17-4.c temp 넣듯이 빈 구조체 하나 넣어서 조정
struct student {
    int id;
    char name[20];
    double grade;
};

int main(void)
{                       // 시작과 동시에 초기화 가능
    struct student s1 = {315, "홍길동", 2.4 },
                   s2 = {316, "이순신", 3.7 },
                   s3 = {317, "세종대왕", 4.4};
    struct student max;

    max = s1;
    if (s2.grade > max.grade) max = s2;
    if (s3.grade > max.grade) max = s3; //구조체 넣을때는 주소나 포인터 없이(특정 상황이면 필요)

    printf("ID: %d\n", max.id);
    printf("Name: %s\n", max.name);
    printf("Grade: %.1lf\n", max.grade);

    return 0;
}