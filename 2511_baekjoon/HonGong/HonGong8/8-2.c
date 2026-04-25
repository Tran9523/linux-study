#include <stdio.h>

int main(void)
{
	int score[5];
	int i;
	int total = 0;
	double avg;

	for (i = 0; i < 5; i++)
	{
		scanf_s("%d", &score[i]);		// 각 배열 요소에 성적 입력
	}

	for (i = 0; i < 5; i++)
	{
		total += score[i];		// 성적을 누적해 총점 계산
	}
	avg = total / 5.0;	// 평균 계산

	for (i = 0; i < 5; i++)
	{
		printf("%5d", score[i]);
	}

	printf("\n");

	printf("평균 : %.1lf\n", avg);

	return 0;

}