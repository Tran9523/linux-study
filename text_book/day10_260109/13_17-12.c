#include <stdio.h>

//17-12.c   typedef = 다시 재정의하기(편해서 자주 씀) 보통 하단 형태로 많이 씀
typedef struct {
    int num;
    double grade;
} Student;      // 대문자인거는 그냥 설정한거지 소문자로 계속 써도 됨
//struct student {
//    int num;
//    double grade;
//};
//typedef struct student Student; // 기존에는 struct student s1 이렇게 작성 => Student
void print_data(Student *ps);

int main(void)
{
    Student s1 = {315, 4.2};

    print_data(&s1);

    return 0;
}
void print_data(Student *ps)
{
    printf("Num: %d\n", ps->num);
    printf("Grade: %.1lf\n", ps->grade);
}