#include <stdio.h>

int main(void)
{
	int a;			// int형 변수 a 선언
	int b, c;		// 2개의 int형 변수 b, c 선언
	double da;		// double형 변수 da 선언
	char ch;		// char형 변수 ch 선언

	a = 10;			// 변수 a에 10 대입	
	b = a;			// 변수 b에 변수 a의 값 대입
	c = a + 20;		// 변수 c에 a + 20 대입
	da = 3.5;		// 변수 da에 3.5 대입	
	ch = 'A';		// 변수 ch에 문자 상수 'A' 대입

	printf("변수 a의 값 : %d\n", a);
	printf("변수 b의 값 : %d\n", b);
	printf("변수 c의 값 : %d\n", c);
	printf("변수 da의 값 : %.1lf\n", da);
	printf("변수 ch의 값 : %c\n", ch);

	return 0;
}