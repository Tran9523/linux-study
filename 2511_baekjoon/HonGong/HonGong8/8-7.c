#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	char str[5];

	str[0] = 'O';
	str[1] = 'K';
	printf("%s\n", str);		// 뒤에 쓰레기값 그대로 출력됨

	return 0;
}