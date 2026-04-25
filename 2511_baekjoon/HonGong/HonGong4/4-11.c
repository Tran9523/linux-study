#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10, b = 20;
	int res;

	res = (++a, ++b); // 차례로 연산되며 결과적으로 증가된 b값이 res에 저장

	printf("a = %d, b = %d\n", a, b);
	printf("res = %d\n", res);

	return 0;
}