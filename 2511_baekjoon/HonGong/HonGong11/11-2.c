#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	char ch1, ch2;

	scanf("%c%c", &ch1, &ch2);	// 2개의 문자를 연속 입력
	printf("%d, %d", ch1, ch2);	// printf("[%c%c]", ch1, ch2);

	return 0;
}