#include <stdio.h>

//15-4.c print에 배열명을 넣으면 주소값이다 리마인드
int main(void)
{
    int ary[5];

    printf("ary의 값: %u\t", ary);
    printf("ary의 주소: %u\n", &ary);
    printf("ary + 1: %u\t", ary +1);    // ary[1]
    printf("&ary + 1: %u\n", &ary + 1); // ary 끝난 다음 주소

    return 0;
}
//ary의 값: 3826578560    ary의 주소: 3826578560
//ary + 1: 3826578564    &ary + 1: 3826578580