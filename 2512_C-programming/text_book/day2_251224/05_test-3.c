#include <stdio.h>

// 문자와 문자열 비교
int main(void)
{
	char grade;
	char name[20];

	printf("학점 입력 : ");
	scanf("%c", &grade);
	printf("이름 입력 : ");
	scanf("%s", name);	// name 배열에 이름 문자열 입력, &를 입력하지 않는게 핵심
	printf("%s의 학점은 %c입니다.\n", name, grade);

	return 0;
}