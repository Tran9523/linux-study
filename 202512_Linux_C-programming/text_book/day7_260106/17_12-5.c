#include <stdio.h>
#include <string.h>

//12-5.c fgets는 개행문자를 포함해옴 - 이전 입력 함수랑 비슷하게 쓰려면 변환필요
int main(void)
{
    char str[80];       // 이게 10이라면 마지막 위치는 널문자가 들어가서 변환 필요 없 

    printf("공백이 포함된 문자열 입력: ");
    fgets(str, sizeof(str), stdin);     // sizeof 넣는걸 생활화 [엔터까지 저장됨]
    printf("전체 문자열 넓이: %ld\n", strlen(str));
    str[strlen(str) -1] = '\0';     // 보충한 내용 &&& strlen = 문자열의 길이
    printf("입력된 문자열은 %s입니다.\n", str);
    printf("이후 문자열 넓이: %ld\n", strlen(str));
    // 버퍼에 \n \0 이 연달아 있어서 자동 엔터 = 즉 개행 엔터까지

    return 0;
}