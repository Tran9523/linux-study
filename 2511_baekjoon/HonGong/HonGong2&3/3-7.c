#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>			// string.h 헤더 파일 포함

int main(void)
{
	char fruit[20] = "strawberry";	// char 배열 선언과 문자열 초기화

	printf("%s\n", fruit);	// strawberry 문자열 출력
	strcpy(fruit, "banana");	// fruit에 banana 복사
	printf("%s\n", fruit);	// 출력 확인

	return 0;
}