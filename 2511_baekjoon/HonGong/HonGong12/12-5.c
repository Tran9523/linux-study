#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[80];

	printf("공백이 포함된 문자열 입력 : ");
	fgets(str, sizeof(str), stdin);		// 인수 3개 사용_배열명&크기확인&표준입력_stdin은 표준 입력 장치(키보드)를 의미
	str[strlen(str) - 1] = '\0';		// fgets 함수는 엔터키까지 입력받기 때문에 마지막에 개행문자가 포함됨. 이를 제거하기 위해 널문자('\0')로 대체
	printf("입력한 문자열은 %s입니다.", str);	

	return 0;
}