#include <stdio.h>

int main(void)
{
	short sh = 32767;	// short형 변수 sh를 최대값으로 초기화
	int in = 2147483647;	// int형 변수 in을 최대값으로 초기화
	long ln = 2147483647;	// long형 변수 ln을 최대값으로 초기화
	long long lln = 123451234512345;	// long long형 변수 lln을 아주 큰 값 초기화

	printf("short 형 변수 sh의 값 : %d\n", sh);
	printf("int 형 변수 in의 값 : %d\n", in);
	printf("long 형 변수 ln의 값 : %ld\n", ln);
	printf("long long 형 변수 lln의 값 : %lld\n", lln); // long long 형은 lld로 출력
	printf("long 형의 크기 : %zd바이트\n", sizeof(long));
	printf("long long 형의 크기 : %zd바이트\n", sizeof(long long));

	return 0;
}