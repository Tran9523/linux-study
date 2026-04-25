#include <stdio.h>

int main(void)
{
	int a;
	int* pa;	// 포인터 선언

	pa = &a;
	*pa = 10;	// 포인터를 이용한 값 대입

	printf("포인터로 a값 출력 : %d\n", *pa);
	printf("변수명으로 a값 출력 : %d\n", a);

	return 0;

}