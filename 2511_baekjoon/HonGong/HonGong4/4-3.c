#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10, b = 20;

	++a;
	--b;

	printf("a : %d\n", a);
	printf("b : %d\n", b);
	
	return 0;
}