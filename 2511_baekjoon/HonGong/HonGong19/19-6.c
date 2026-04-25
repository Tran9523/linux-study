#include <stdio.h>
#define VER 7
#define BIT16

int main(void)
{
	int max;

#if VER >= 6
	printf("버젼 %d입니다.\n", VER);
#else
#error 컴파일러 버젼은 6.0 이상이어야 합니다.
#endif

#ifdef BIT16					// = if defined BIT16
	max = 32767;
#else
	max = 2147483647;
#endif

	printf("int형 변수의 최댓값 : %d\n", max);

	return 0;
}