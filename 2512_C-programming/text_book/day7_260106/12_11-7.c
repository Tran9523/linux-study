#include <stdio.h>
//11-7.c / fgets_string & fgetc_char 임
// fgets(str, sizeof(str), stdin) 형태 기억
int main(void)
{
    int num, grade;
    printf("학번 입력: ");
    scanf("%d", &num);
    //getchar();          // 버퍼를 받아서 빼냄 = 버려버림 / 없으면 엔터치고 학점 없이 끝
    printf("학점 입력: ");
    //grade = getchar();      // 혹은 얘를 scanf로 받으면 없이 가능
    scanf(" %c", &grade);       // 그래서 앞에 공백 주면 넘기고 가능
    printf("학번: %d, 학점: %c", num, grade);   // 버퍼 남아있으면 아래 엔터까지 합쳐서 2번
    printf("\n");

    return 0;

}