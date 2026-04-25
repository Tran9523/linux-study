#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	register int i;
	auto int sum = 0;

	for (i = i; i <= 10000; i++)
	{
		sum += i;
	}

	printf("%d\n", sum);

	return 0;
}