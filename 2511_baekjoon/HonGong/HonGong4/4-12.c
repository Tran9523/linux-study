#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10, b = 20, res;

	res = (a > b) ? a : b; // a와 b 중에 큰 값이 res에 저장_엑셀 if문과 비슷, 참이면 2 거짓이면 3
	printf("큰 값 : %d\n", res);

	return 0;
}