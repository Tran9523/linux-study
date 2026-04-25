#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void my_gets(char* str, int size);

int main(void)
{
	char str[7];

	my_gets(str, sizeof(str));
	printf("입력한 문자열 : %s\n", str);

	return 0;
}

void my_gets(char* str, int size)
{
	int ch;
	int i = 0;

	ch = getchar();
	while ((ch != '\n') && (i < size - 1))
	{
		str[i] = ch;
		i++;
		ch = getchar();		// 새로운 문자를 배열에 저장하고 첨자증가 & 새로운 문자 입력
	}
	str[i] = '\0';		// 입력한 문자 마지막엔 널
}