#include <stdio.h>
//13-8.c - 다음에 시간 되면 하나 받고 자체적으로 곱하는거 해서 쓸 수 있는지 확인 (검증 제대로)
// 주소를 주지 않는 한 불가능 => 값을 받아서 자체적으로 복사해서 쓰는거라, 복사된 값을 받아서 넣는게 아니면 불가
//정적 지역 변수나 전역 변수와 같이 함수가 반환된 후에도 저장 공간이 유지되는 경우만 주소를 반환
int *sum(int a, int b);
int *mul(int a);

int main(void)
{
    int *resp;
    int *multi;
    resp = sum(10,20);
    printf("두 정수의 합: %d\n", *resp);

    multi = mul(10);
    printf("정수값 확인: %d\n", *multi);
    multi = mul(10);
    printf("정수값 확인: %d\n", *multi);
    multi = mul(10);
    printf("정수값 확인: %d\n", *multi);
    return 0;
}
int *sum(int a, int b)
{
    static int res;

    res = a + b;

    return &res;        // 주소를 주는게 핵심 (구 컴파일러에서 int* 로 표시되는 이유)
}
int *mul(int a)
{
    static int result;

    result = (a * 2) + 1;

    return &result;
}