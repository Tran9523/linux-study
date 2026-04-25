#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10, b = 5;
	int res;

	res = a / b * 2;
	printf("res = %d\n", res);
	res = ++a * 3;
	printf("res = %d\n", res);
	res = a > b && a != 5; // a>b 결과와 a != 5 결과를 && 연산
	printf("res = %d\n", res);
	res = a % 3 == 0; // a % 3의 값이 0과 일치하는지
	printf("res = %d\n", res);

	return 0;
}