#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 8-5.c strcpy 문자넣기
int main(void)
{
    char str1[80] = "cat";
    char str2[80];

    strcpy(str1, "tiger");
    strcpy(str2, str1);
    printf("%s, %s\n", str1, str2);

    return 0;
}