#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//17-2.c 구조체로 입출력 해보기

#define SIZE 81
struct profile{
    char name[20];
    int age;
    double height;
    char *intro;
};

int main(void)
{
    struct profile yuni;

    strcpy(yuni.name, "서하윤");
    yuni.age = 17;
    yuni.height = 164.5;

    //yuni.intro = (char *)malloc(80));
    yuni.intro = (char *)calloc(SIZE, sizeof(char));
    if (yuni.intro == NULL) {
        printf("# 메모리가 부족합니다.");
        exit(1);
    }
    printf("자기소개 [최대: %d자]: ", SIZE-1);
    fgets(yuni.intro, SIZE, stdin);
    //gets(yuni.intro); 오류가 나기 너무 쉬운 함수인 gets

    printf("이름:\t%s\n", yuni.name);
    printf("나이:\t%d\n", yuni.age);
    printf("키:\t%.1lf\n", yuni.height);
    printf("자기소개: %s\n", yuni.intro);
    free(yuni.intro);

    return 0;
}