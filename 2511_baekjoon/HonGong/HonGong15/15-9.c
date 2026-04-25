#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10;
	double b = 3.5;
	void* vp;

	vp = &a;
	printf("a : %d\n", *(int*)vp);
	printf("a의 주소 + 1의 값 : %u\n", (int*)vp + 1);

	vp = &b;
	printf("b : %.1lf\n", *(double*)vp);

	return 0;
}