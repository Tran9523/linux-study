#include <stdio.h>
#include <string.h>
//12-11.c + strlen를 표현할 함수 만들기

int length(char *p);
int main(void)
{
    char str1[80], str2[80];
    char *resp;

    printf("2개의 과일 이름 입력: ");
    scanf("%s%s", str1, str2);
    if (strlen(str1) > strlen(str2))
        resp = str1;
    else
        resp = str2;
    printf("이름이 긴 과일은: %s\n", resp);
    printf("str1 & str2의 길이 strlen 함수: %d, %d\n", strlen(str1), strlen(str2));
    printf("내 함수로 구현한 길이: %d, %d\n", length(str1), length(str2));

    return 0;
}

int length(char *p)
{
    int i = 0;

    while (1) {
        if (p[i] != '\0')
            i++;
        else
            break;
    }

    return i;
}