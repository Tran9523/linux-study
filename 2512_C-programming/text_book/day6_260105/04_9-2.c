#include <stdio.h>

//9-2.c 포인터와 변수 주소
int main(void)
{
    int a;  // ex. 100번지에 a
    int *pa;    // ex. 200번지에 *pa - 여기서 int는 가리킬 값, 내가 int라는게 아님

    pa = &a;    // 200번지에 100번지 '주소' 입력 = pa -> a
    *pa = 10;   // 100번지'의 값'에 10 입력

    printf("포인터로 a 값 출력: %d\n", *pa);
    printf("변수명으로 a 값 출력: %d\n", a);

    return 0;
}