//1st - ??! 자체의 함의로 컴파일이 제대로 안됨. 그리고 이어붙이기니까 굳이 문장 자체를 만들 필요 X
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[60] = {0};
    char str2[5] = "??!";
    fgets(str, sizeof(str), stdin);
    strcpy(str, str2);

    printf("%s", str);

    return 0;

}