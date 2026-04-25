#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//16-4.c 뒤에 for문도 한꺼번에 작성해도 됨 어차피 받고 푸는거라
int main(void)
{
    char temp[80];
    char *str[3];
    int i;

    for (i = 0; i < 3; i++) {
        printf("문자열을 입력하세요: ");
        gets(temp);
        str[i] = (char *)malloc(strlen(temp) + 1);  // 뒤에 널 받을 공간까지 +1
        strcpy(str[i], temp);
    }
    
    for (i = 0; i < 3; i++) {
        printf("%s\n", str[i]);
    }

    for (i = 0; i < 3; i++) {
        free(str[i]);
    }

    return 0;
}