#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int score[2][3][4] = {			//	2개 반 3명의 4과목 성적
		{ { 72, 80, 95, 60 }, { 68, 98, 83, 90 }, { 75, 72, 84, 90 } },
		{ { 66, 85, 90, 88 }, { 95, 92, 88, 95 }, { 43, 72, 56, 75 } }
	};

	int i, j, k;

	for (i = 0; i < 2; i++)
	{
		printf("%d반 점수...\n", i + 1);
		for (j = 0; j < 3; j++)
		{
			for (k = 0; k < 4; k++)
			{
				printf("%5d", score[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}

// 14-1 test 문제
/* char mark[5][5] = {0};
int i, j;
for (i = 0; i < 5; i++)
{
	for (j = 0; j < 5; j++)
	{
		if ((i == j) || (i == (4 - j)) mark[i][j] = 'X';		// (i + j) == 4 여도 괜찮다고 함
	}
}
*/