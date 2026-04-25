#include <stdio.h>
//15-8.c 함수포인터의 사용
void func(int (*fp)(int, int));
int sum(int a, int b);
int mul(int a, int b);
int max(int a, int b);

int main(void)
{
    int sel;

    printf("두 정수의 합 [1]\n");
    printf("두 정수의 곱 [2]\n");
    printf("두 정수 중에서 큰 값 계산 [3]\n");
    printf("원하는 연산을 선택하세요: ");
    scanf("%d", &sel);

    switch (sel) {
        case 1: func(sum); break;
        case 2: func(mul); break;
        case 3: func(max); break;
        default: printf("입력 오류"); break;
    }

    return 0;
}
void func(int (*fp)(int, int))
{
    int a, b;
    int res;
                    //func의 변수로 fp를 줬음 = 기억 
    printf("두 정수의 값을 입력하세요: ");
    scanf("%d %d", &a, &b);
    res = fp(a, b);
    printf("결과값은 [%d]\n", res);
}

int sum(int a, int b)
{
    return (a + b);
}

int mul(int a, int b)
{
    return (a * b);
}

int max(int a, int b)
{
    if (a > b) return a;
    else return b;
}
//  01 두 정수의 합
//  02 두 정수의 곱
//  03 두 정수 중에서 큰 값 계산
//  원하는 연산을 선택하세요: 1
//  두 정수의 값을 입력하세요: 10 15
//  결과값은 [25]