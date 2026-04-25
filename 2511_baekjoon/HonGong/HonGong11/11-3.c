#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int ch;

	ch = getchar();		// 입력 문자를 저장할 변수
	printf("입력한 문자 : ");
	putchar(ch);
	putchar('\n');

	return 0;
}