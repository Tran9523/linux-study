#include <stdio.h>

//10-3.c 배열 주소 및 더미값 확인하는 코드 추가
int main(void)
{
    int ary[3] = { 10, 20, 30};
    int *pa = ary;
    int i;
    char ary_a[2] = {'a', 'A'};
    char *pc = ary_a;

    printf("배열의 값과 주소: \n");
    for (i=0; i<3; i++) {
        printf("%d\t", *pa);
        printf("%p\n", pa); //gpt 추천은 %u 보다 %p
        pa++;
    }
    printf("\n더미값 확인\n");
    
    for(i=0; i<5; i++) {
        printf("%d\t", *pc);
        pc++;
    }
    
    return 0;
}