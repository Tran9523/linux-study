#include <stdio.h>
#include <stdlib.h>

//16-1.c '공간을 잡고 있다'표현 유의
//C언어에서는 캐스팅 안해도 된다함 [ pi = malloc(sizeof(int)) ]
int main(void)
{
    int *pi;
    double *pd;
                    //(int *)malloc(4) 와 같음
    pi = (int *)malloc(sizeof(int));    //int의 사이즈(4byte)로 공간배정(heap영역)
    if (pi == NULL) {
        printf("# 메모리가 부족합니다.\n"); //if 백만 배정(연속되야함) - 없으면 NULL 반환
        exit(1);                        //그걸 확인하는 과정
    }

    pd = (double *)malloc(sizeof(double));  // 그럼 여기도 확인해야???
    if (pd == NULL) {
        printf("# 메모리가 부족합니다.\n");
        free(pi);                   // 앞에서 할당한거 정리
        exit(1);
    }

    *pi = 10;       // malloc 할당된 영역은 이름도 없지만 포인터로 사용 가능
    *pd = 3.4;

    printf("int : %d\n", *pi);
    printf("double: %.1lf\n", *pd);

    free(pi);       // 반환 필수 <- 메모리 누수가 발생함
    free(pd);

    return 0;
}