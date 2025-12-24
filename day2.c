#include <stdio.h>

// 예제 4-8
int main(void)
{
    int a = 20, b = 3;
    double res;
    double c = 551530.109;

    res = ( (double)a ) / ( (double)b );
    printf("a = %d, b = %d\n", a, b);
    printf("a / b 의 결과 : %d\n", (a / b));
    printf("a / b 의 결과 : %.10lf\n", res);

    a = (int)res;
    printf("(int) %.1lf의 결과 : %d\n", res, a);
    printf("%5.2lf\n", c);

    return 0;
}

/* 예제 4-13
int main(void)
{
    int a = 10;
    int b = 12;

    printf("a & b : %d\n", a & b);
    printf("a ^ b : %d\n", a ^ b);
    printf("a | b : %d\n", a | b);
    printf("~a : %d\n", ~a);
    printf("a << 1 : %d\n", a << 1);
    printf("a >> 2 : %d\n", a >> 2);
    
    return 0;
}

 예제 4-12
int main(void)
{
int a = 10, b = 20, res;

res = (a > b) ? a : b;
printf("큰 값 : %d\n", res);

return 0;
}

  예제 4-7
int main(void)
{
    int a = 30;
    int res;

    res = (a > 10) && (a < 20);
    printf("1st %d\n", res);
    res = (a < 10) || (a > 20);
    printf("2nd %d\n", res);
    res = !(a >= 30);
    printf("3rd %d\n", res);
    
    return 0;
}

    예제 4인가
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

    예제
int main(void)
{
	int a, b;
	int sum, sub, mul, inv;

	a = 10;
	b = 20;
	sum = a + b;
	sub = a - b;
	mul = a * b;
	inv = -a;

	printf("a의 값 : %d, b의 값 : %d\n", a, b);
	printf("덧셈 : %d\n", sum);
	printf("뺄셈 : %d\n", sub);
	printf("곱셈 : %d\n", mul);
	printf("a의 음수 연산 : %d\n", inv);

	return 0;
}

    예제
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

    예제
int main(void)
{
	int age;
	double height;

	printf("나이와 키를 입력하세요 : ");
	scanf("%d%lf", &age, &height);
	printf("나이는 %d살, 키는 %.1lfcm입니다\n", age, height);

	return 0;
}

    예제
int main(void)
{
    int a;
    scanf("%d", &a);    // & 주소의 의미
    printf("입력된 값 : %d\n", a);

    return 0;
}
  예제 2-4.c
int main(void)
{
    printf("%d\n", 10);
    printf("%lf\n", 3.4);
    printf("%.1lf\n", 3.45);    // 0.1까지 표현이라 반올림 되서 3.5
    printf("%.10lf\n", 3.4);

    printf("%d + %d = %d\n", 10, 20, 10 + 20);
    printf("%.1lf - %.1lf = %.1lf\n", 3.4, 1.2, 3.4 - 1.2);

    return 0;

}

    예제 2-3.c
int main(void)
{
    printf("Be happy\n");
    printf("1235678901234567890\n");
    printf("My\tfriend\n");
    printf("Goot\bd\tchance\n");
    printf("Cow\rW\a\n");   //  123

    return 0;
}
    */