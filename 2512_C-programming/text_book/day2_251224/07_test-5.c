#include <stdio.h>

// 숫자와 문자열
int main(void)
{
	double apple;
	int banana;
	int orange;
    int a, b, c;
    
    b = a;
    c = a + 10;
    a = 20;

	apple = 5.0 / 2.0;
	banana = 5 / 2;
	orange = 5 % 2;

    printf("a = %d, b = %d, c = %d", a, b, c);
	printf("apple : %.1lf\n", apple);
	printf("banana : %d\n", banana);
	printf("orange : %d\n", orange);

	return 0;
}