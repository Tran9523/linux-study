#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
	int n;
	int pn;
	int cnt = 0;

	scanf_s("%d", &n);
	int i, j;
	for (i = 2; i <= n; i++)
	{
		pn = 1;
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
			{
				pn = 0;
				break;
			}
		}
		if (pn == 1)
		{
			printf("%5d", i);
			cnt++;
				if ((cnt % 5) == 0)
					printf("\n");
		}
	}
}