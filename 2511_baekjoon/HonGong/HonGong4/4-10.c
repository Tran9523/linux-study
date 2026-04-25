#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10, b = 20;
	int res = 2;

	a += 20; // a에 20을 더해서 저장
	res *= b + 10; // b에 10을 더한 값을 res에 곱해서 저장

	printf("a = %d, b = %d\n", a, b);
	printf("res = %d\n", res);

	return 0;
}