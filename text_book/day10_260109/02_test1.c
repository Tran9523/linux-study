#include <stdio.h>

//test1 패딩바이트 크기 줄여보기
//어디에 진짜 비었는지 주소값으로 확인이 가능함(나중에 시간된다면 꼭 확인)
struct student1 {
    char ch1;
    short num;
    char ch2;
    int score;
    double grade;
    char ch3;
};

struct student2 {
    char ch1;
    short num;
    char ch2;
    char ch3;
    int score;
    double grade;
};

struct student3 {
    char ch1;
    short num;
    char ch2;
    int score;
    double grade;
    char ch3;
    int score2
};

int main(void)
{
    struct student1 s1;
    struct student2 s2;
    struct student3 s3;

    printf("s1의 사이즈: %ld\n", sizeof(s1));
    printf("s2의 사이즈: %ld\n", sizeof(s2));
    printf("s3의 사이즈: %ld\n", sizeof(s3));

    return 0;
}
//  s1의 사이즈: 32
//  s2의 사이즈: 24
//  s3의 사이즈: 32