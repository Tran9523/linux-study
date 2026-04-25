#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[80];
	char res_str[80];		// 생략할 문자열 임시 저장
	char* star = "**********";
	int len;
	printf("단어 입력 : ");
	scanf("%s", str);
	len = strlen(str);
	if (len <= 5)
	{
		strcpy(res_str, str);
	}
	else
	{
		strncpy(res_str, str, 5);	// 5글자 저장
		res_str[5] = '\0';
		strncat(res_str, star, len - 5);
	}
	printf("입력한 단어 : %s, 생략한 단어 : %s\n", str, res_str);
	return 0;
}
