#include <stdio.h>

int main(void)
{
	printf("Be happy\n");	// 문자열 "Be happy" 출력하고 줄 바꿈
	printf("12345678901234567890\n"); // 20글자 출력하고 줄 바꿈
	printf("My\tfreind\n");	// My를 출력하고 탭 위치로 이동 후에 friend 출력하고 줄 바꿈
	printf("Goot\bd\tchance\n");	// Goot를 출력하고 한 칸 왼쪽으로 이동후 t를 d로 바꾸고 탭 이동 후 Chance 입력
	printf("Cow\rW\a\n");	// Cow 입력 후 맨 앞으로 이동하고 W로 바꾸고 벨소리를 내고 줄 바꿈

	return 0;
}