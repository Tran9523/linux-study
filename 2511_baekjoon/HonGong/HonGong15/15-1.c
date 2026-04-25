#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a = 10;
	int* pi;
	int** ppi;		//	 이중 포인터 선언

	pi = &a;
	ppi = &pi;

	printf("--------------------------------------\n");
	printf("변수	변숫값	&연산	*연산	**연산\n");
	printf("--------------------------------------\n");
	printf("  a%12d%12u\n", a, &a);
	printf(" pi%12u%12u%12d\n", pi, &pi, *pi);
	printf("ppi%12u%12u%12u%12u\n", ppi, &ppi, *ppi, **ppi);
	printf("--------------------------------------\n");

	return 0;
}