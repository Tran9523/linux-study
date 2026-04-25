#include <stdio.h>

//10-5.c 내부 함수 이용해서 출력
void print_ary(int *pa);    // 뒤에 붙이는 함수를 쓰는 이유는 가독성, main을 위해서

int main(void)
{
    int ary[5] = {10, 20, 30, 40, 50};

    print_ary(ary);

    return 0;
}

void print_ary(int *pa)     // 이걸 통해 ary를 별도로 제작 안해도 메인 함수에 접근 가능
{
    int i;

    for (i = 0; i < 5; i++) {
        printf("%d ", pa[i]);
    }
}