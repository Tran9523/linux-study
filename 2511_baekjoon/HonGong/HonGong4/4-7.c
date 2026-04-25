#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10, b = 20, res;

	a + b;
	printf("%d + %d = %d\n", a, b, a + b);

	res = a + b;
	printf("%d + %d = %d\n", a, b, res);

	return 0;
}