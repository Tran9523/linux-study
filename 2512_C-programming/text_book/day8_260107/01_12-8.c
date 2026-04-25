#include <stdio.h>
#include <string.h>
//12-8.c     문자열 교체, strcpy으로 교체하면 널 후에는 기존 문자 남아있음

int main(void)
{
    char str1[80] = "strawberry";
    char str2[80] = "apple";
    char *ps1 = "banana";       // 변수 안에 넣는게 아닌 어딘가에 banana를 찾아 포인터
    char *ps2 = str2;

    printf("최초 문자열: %s\n", str1);

    strcpy(str1, str2);     // apple \0 erry \0
    printf("str2로 바꾼 문자열: %s\n", str1);
    printf("후단까지 체크해보기: %c\n", str1[9]);

    strcpy(str1, ps1);
    printf("ps1으로 바꾼 문자열: %s\n", str1);
    printf("후단까지 체크해보기: %c\n", str1[9]);

    strcpy(str1, ps2);
    printf("ps2로 바꾼 문자열: %s\n", str1);

    strcpy(str1, "banana");
    printf("문자 직접 바꾼 문자열: %s\n", str1);
    
    return 0;   
    
}