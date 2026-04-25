#include <stdio.h>
//15-2.c
// 100, 200, 300, 400 생각하면서 그림그리기 (ppa, ppb는 주소 500, 600)
void swap_ptr(char **ppa, char **ppb);

int main(void)
{
    char *pa = "success";
    char *pb = "failure";

    printf("pa -> %s, pb -> %s\n", pa, pb);
    swap_ptr(&pa, &pb);             // **를 받으니까 포인터(pa)의 & 달고 전달
    printf("pa -> %s, pb -> %s\n", pa, pb);

    return 0;
}

void swap_ptr(char **ppa, char **ppb)       // 여기서 별의 개수 및 의미 파악
{
    char *pt;

    pt = *ppa;
    *ppa = *ppb;
    *ppb = pt;
}