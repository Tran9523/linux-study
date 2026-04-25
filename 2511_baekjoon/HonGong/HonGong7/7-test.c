#include <stdio.h>

int rec_func(int n);

int main(void)
{
	int res;

	res = rec_func(50);

	printf("%d", res);

	return 0;
}

int rec_func(int n)
{
	int res;

	if (n == 1)
		return 1;
	else
		res = n + rec_func(n - 1);

	return res;
}