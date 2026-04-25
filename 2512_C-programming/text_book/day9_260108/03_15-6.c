#include <stdio.h>

//15-6.c (*pa)[4] = ary[][4] 즉 뒤에 '열이 4개'
void print_ary(int (*)[4]);     // 열 의미하는 [4] + 여기다가 포인트 형태로 줄꺼야~

int main(void)
{
    int ary[3][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
    print_ary(ary); // 여기서 ary 주면 저기서 그 주소로 받는 그런 느낌인가봄

    return 0;
}
void print_ary(int (*pa)[4])    // 동일 의미 (*pa) = pa[]
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%5d", pa[i][j]);
        }
        printf("\n");
    }
}
//    1    2    3    4
//    5    6    7    8
//    9   10   11   12