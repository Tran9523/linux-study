#include <stdio.h>

int main(void)
{
	int a = 10;
	int* p = &a;
	double* pd;

	pd = p;
	printf("&lf\n", *pd);

	return 0;

	/* double a = 3.4;
	double* pd = &a;
	int* pi;
	pi = (int*)pd;	*/
}