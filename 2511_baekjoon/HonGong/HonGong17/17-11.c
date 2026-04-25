#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

enum season { SPRING, SUMMER, FALL, WINTER };

int main(void)
{
	enum season ss;
	char* pc = NULL;

	ss = SPRING;	// 열거 멤버의 값 대입
	switch (ss)
	{
	case SPRING:
		pc = "inline"; break;
	case SUMMER:
		pc = "swimming"; break;
	case FALL:
		pc = "trip"; break;
	case WINTER:
		pc = "skiing"; break;
	}
	
	printf("나의 레저 활동 => %s\n", pc);

	return 0;
}