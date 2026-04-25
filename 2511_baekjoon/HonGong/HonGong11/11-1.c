#include <stdio.h>

int main(void)
{
	char small, cap = 'G';

	if ((cap >= 'A') && (cap <= 'Z')) // 대문자 범위라면
	{
		small = cap + ('a' - 'A');
	}
	printf("대문자 : %c %c", cap, "\n");	// \n을 %c로 출력하면 줄이 바뀜
	printf("소문자 : %c", small);

	return 0;
}