#include <stdio.h>

int main(void)
{
	int a = 10, b = 20;
	const int* pa = &a;

	printf("변수 a값 : %d\n", *pa);
	pa = &b;
	printf("변수 b값 : %d\n", *pa);		// b를 간접 참조하면 pa값 변경해서 출력 가능
	pa = &a;
	a = 20;								//	만약 *pa=20 으로 사용 시 에러메시지 출력됨
	printf("변수 a값 : %d\n", *pa);

	return 0;
}