#include <stdio.h>

//연습 문제 (이중포인터의 구조 이해)
//예상 - a 10 / b 20  - pa 20 / pb 10 [일치함]
int main(void)
{
    int a = 10, b = 20;
    int *pa = &a, *pb = &b;
    int **ppa = &pa, **ppb = &pb;
    int *pt;

    pt = *ppa;
    *ppa = *ppb;
    *ppb = pt;

    printf("a: %d\tb: %d\n", a, b);
    printf("*pa: %d\t*pb: %d\n", *pa, *pb);

    return 0;
}
//  a: 10   b: 20
//  *pa: 20 *pb: 10