#include <stdio.h>

//9-4.c const int 선언했을때 차이점
int main(void)
{
    int a = 10, b = 20;
    const int *pa = &a;     // pa = 20; (X) a는 pa를 간접 참조하여 바꿀 수 없다(const)
                            // 없으면 *pa = 20; 으로 마지막에 20 출력 가능
    printf("변수 a값: %d\n", *pa);
    pa = &b;
    printf("변수 b값: %d\n", *pa);
    pa = &a;
    printf("주소만 변경했을 때: %d\n", *pa);
    a = 20;
    printf("변수 a값: %d\n", *pa);  // sizeof(pa) = 8, sizeof(*pa) = 4

    return 0;
}
