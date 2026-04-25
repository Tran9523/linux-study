#include <stdio.h>

//12-6.c
int main(void)
{
    int age;
    char name[20];
    
    printf("나이 입력: ");
    scanf("%d", &age);
    gets();           //마찬가지로 버퍼로 못 받으니까 버리기
    //  getchar(); & scanf("%*c"); & fgetc(stdin); 등 사용가능
    printf("이름 입력: ");
    gets(name);
    printf("나이: %d, 이름: %s\n", age, name);

    return 0;
}