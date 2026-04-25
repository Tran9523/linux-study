#include <stdio.h>

int main(void)
{
	int income = 0;	// 소득 변수 선언 및 초기화
	double tax;		// 세금 변수 선언
	const double tax_rate = 0.12;	// 세율 상수 선언 및 초기화
	// tax_rate = 0.15;		// 컴파일 오류 테스트

	income = 456;	// 소득액 저장
	tax = income * tax_rate;	// 세금 계산
	printf("세금은 : %.1lf입니다.\n", tax);

	return 0;
}