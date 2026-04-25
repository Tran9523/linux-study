#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	printf("apple이 저장된 시작 주소 값 : %p\n", "apple");
	printf("Second Adress : %p\n", "apple" + 1);
	printf("First Word : %c\n", *"apple");
	printf("Second Word : %c\n", *("apple" + 1));
	printf("배열로 표현한 세번째 문자 : %c\n", "apple"[2]);

	return 0;
}