#include <stdio.h>

//성적처리 시스템 (5명의 학번, 이름, 국어, 영어, 수학) -> 총점 / 평균 / 등급
#define NUMBER 5

typedef struct {
    int num;    char grade;
    int kor;    int eng;
    int math;   int total;
    double avg;
    char name[16];
} stu;

void scanf_array(stu list[], int n);
void sort_array(stu list[], int n);
void clear_stdin(void);
void print_array(stu list[], int n);

int main(void)
{
    stu list[NUMBER];      //선언 하는 방식에 대해서 항상 생각하기

    scanf_array(list, NUMBER);

    printf("정렬 전 데이터\n");
    print_array(list, NUMBER);
    

    sort_array(list, NUMBER);

    printf("정렬 후 데이터\n");
    print_array(list, NUMBER);

    return 0;
}

void scanf_array(stu list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("학번: ");
        if (scanf("%d", &list[i].num) != 1) {
            printf("학번은 숫자만 입력하세요.\n");
            clear_stdin();
            i--;        // i 줄이는게 핵심
            continue;
        }
        clear_stdin();
        printf("이름: ");
        scanf("%15s", list[i].name);
        clear_stdin();
        printf("국어, 영어, 수학 점수: ");
        if (scanf("%d %d %d", &list[i].kor, &list[i].eng, &list[i].math) != 3) {
            printf("점수는 숫자 3개로 입력하세요.\n");
            clear_stdin();
            i--;
            continue;
        }
        clear_stdin();
        list[i].total =  list[i].kor + list[i].eng + list[i].math;
        list[i].avg = list[i].total / 3.0;
        if ((list[i].avg) >= 90) {
            list[i].grade = 'A';
        } else if ((list[i].avg) >= 80) {
            list[i].grade = 'B';
        } else if ((list[i].avg) >= 70) {
            list[i].grade = 'C';
        } else {
            list[i].grade = 'F';
        }
        clear_stdin();
        printf("[%d]명 입력 완료 - 전체 %d명\n", i+1, n);
    }
}

void sort_array(stu list[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n -1 - i; j++) {
            if (list[j].avg < list[j + 1].avg) {
                stu tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
}

void print_array(stu list[], int n)
{
    printf("학번/이름:\t국어/영어/수학     총점 / 평균 / 학점\n");
    for (int i = 0; i < n; i++) {
        printf("%d/%s:\t%3d /%3d /%3d     %4d / %4.1lf / %c",
            list[i].num, list[i].name, list[i].kor, list[i].eng, list[i].math,
            list[i].total, list[i].avg, list[i].grade);
        printf("\n");
    }
}

void clear_stdin(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}