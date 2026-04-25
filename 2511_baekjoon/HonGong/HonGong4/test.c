#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	double weight, height, bmi;
	int res;

	printf("몸무게(kg)와 키(cm) 입력 : ");
	scanf_s("%lf%lf", &weight, &height);
	
	height /= 100;
	bmi = weight / (height * height);
	res = (bmi >= 20) && (bmi < 25);
	printf("%s\n", (res == 1) ? "표준입니다." : "체중관리가 필요합니다.");

	return 0;
}