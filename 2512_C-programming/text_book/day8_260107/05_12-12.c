#include <stdio.h>
#include <string.h>
//12-12.c strcmp 주석과는 다르게 얼마나 차이나는지 값이 출력됨

int main(void)
{
    char str1[80] = "pear";
    char str2[80] = "peach";

    printf("사전에 나중에 나오는 과일 이름: ");     // 아스키코드 그대로 앞 번호라 대문자가 앞
    if (strcmp(str1, str2) > 0)     // 나중에 나오면 1, 아니면 -1, 같으면 0
        printf("%s\n", str1);       // str1이 str2보다 먼저 나오면 -1 = 순서 주의
    else                            // 즉 아스키 코드가 뒤에 있으면 1
        printf("%s\n", str2);

    return 0;
}