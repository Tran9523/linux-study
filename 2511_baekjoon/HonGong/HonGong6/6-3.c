#include <stdio.h>

int main(void)
{
	int a = 1;

	do
	{
		a = a * 2;
	} while (a < 10);	// 여기 세미클론 기억
	printf("a : %d\n", a);

	return 0;
}