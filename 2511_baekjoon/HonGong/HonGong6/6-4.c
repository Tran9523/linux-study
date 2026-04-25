#include <stdio.h>

int main(void)
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 5; j++)
		{
			printf("*");
		}
		printf("\n");
	}

	return 0;
}

/*
int main(void)
{
	int i, j;

	for ( i = 2; i <= 9; i++)
	{
		for ( j = 1; j <= 9; j++)
		{
			printf("%d * %d = %d\n", i, j, i * j);
		}
	}
	
	return 0;
}
		*/