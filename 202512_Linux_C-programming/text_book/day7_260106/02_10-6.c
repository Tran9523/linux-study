#include <stdio.h>
//10-6.c cf. 복습할때 숫자말고 문자열로도 해보기 + print_ary에서 size 해보기
#define ARY_LEN(x) (sizeof(x) / sizeof((x)[0]))
void print_ary(int *pa, int size);

int main(void)
{
    int ary1[5] = {10, 20, 30, 40, 50};
    int ary2[7] = {10, 20, 30, 40, 50, 60, 70};

    print_ary(ary1, 5);
    
    print_ary(ary2, ARY_LEN(ary2));

    return 0;
}

void print_ary(int *pa, int size)       // 같은 동작 반복하기 위해 함수 + 옆에 적히는게 선언
{
    int i;

    for (i = 0; i < size; i++) {
        printf("%d ", pa[i]);
    }
    printf("\n");       // 편의를 위해 여기로 옮김 원래 위치는 main 함수
}