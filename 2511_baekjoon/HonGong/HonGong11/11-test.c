#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	char ch;
	int len, max = 0;

	while (1)
	{
		ch = getchar();
		if (ch == EOF)
			break;
		len = 0;
		while (ch != '\n')
		{
			len++;
			ch = getchar();
		}
		//	printf("길이 : %d\n", len);
		if(len > max)
		{
			max = len;
		}
		printf("\n");
	}

	printf("길이가 가장 긴 문장의 길이 : %d\n", max);

	return 0;
}