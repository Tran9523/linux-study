#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define STUDENT_COUNT 5

typedef struct
{
    int id;
    char name[20];
    int kor, eng, math;
    int total;
    double avg;
    char grade;
} Student;

/* 학점 계산 함수 */
char get_grade(double avg)
{
    if (avg >= 90) return 'A';
    else if (avg >= 80) return 'B';
    else if (avg >= 70) return 'C';
    else return 'F';
}

/* 학생 정보 출력 */
void print_students(Student s[])
{
    int i;
    for (i = 0; i < STUDENT_COUNT; i++)
    {
        printf("%6d  %-8s  %3d  %3d  %3d  %3d  %5.1f   %c\n",
            s[i].id, s[i].name,
            s[i].kor, s[i].eng, s[i].math,
            s[i].total, s[i].avg, s[i].grade);
    }
}

/* 총점 기준 정렬 */
void sort_by_total(Student s[])
{
    int i, j;
    Student temp;

    for (i = 0; i < STUDENT_COUNT - 1; i++)
    {
        for (j = 0; j < STUDENT_COUNT - 1 - i; j++)
        {
            if (s[j].total < s[j + 1].total)
            {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

int main(void)
{
    Student stu[STUDENT_COUNT];
    int i;

    /* 입력 */
    for (i = 0; i < STUDENT_COUNT; i++)
    {
        printf("학번 : ");
        scanf("%d", &stu[i].id);

        printf("이름 : ");
        scanf("%s", stu[i].name);

        printf("국어, 영어, 수학 점수 : ");
        scanf("%d %d %d",
            &stu[i].kor, &stu[i].eng, &stu[i].math);

        stu[i].total = stu[i].kor + stu[i].eng + stu[i].math;
        stu[i].avg = stu[i].total / 3.0;
        stu[i].grade = get_grade(stu[i].avg);

        printf("\n");
    }

    /* 정렬 전 출력 */
    printf("# 정렬 전 데이터...\n");
    print_students(stu);

    /* 정렬 */
    sort_by_total(stu);

    /* 정렬 후 출력 */
    printf("\n# 정렬 후 데이터...\n");
    print_students(stu);

    return 0;
}