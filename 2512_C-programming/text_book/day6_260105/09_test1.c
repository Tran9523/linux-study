#include <stdio.h>

//형변환 테스트
int main(void)
{
    int a = 10;
    int *p = &a;
    double *pd;
//    double *ps;   // 주소 확인용 값 추가1

//    pd = p;             // 기본
//    (int *)pd = p;      // 1번 -- 뒤를 기본 형태로 가면 어쨌든 5~8 번째에서 쓰레기값
    pd = (double *)p;   // 2번 -- 어차피 뒤에서 더블로 읽는 순간 불가능
//    ps = p;       // 주소 확인용 값 추가2

    printf("%lf\n", *pd); // 기본
//    printf("%lf\n", *ps); // 주소 확인용 값 추가3
//    printf("%d\n", *(int *)pd); // 3반 -- * 붙이면 가능 / 형 변환하고 포인터 처리까지
    
    return 0;
}