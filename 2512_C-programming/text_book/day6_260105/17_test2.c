#include <stdio.h>

// 왜 3번째 ary가 0으로 나오는지 체크용 gpt 코드
int main(void) {
    int ary[3] = {10,20,30};
    int *pa = ary;
    int i = 12345;              // 일부러 0이 아닌 값으로 시작
    char ary_a[2] = {'a','A'};
    unsigned char *p = (unsigned char*)ary_a;

    printf("&ary_a[0]=%p, &ary_a[1]=%p\n", (void*)&ary_a[0], (void*)&ary_a[1]);
    printf("&i=%p\n", (void*)&i);

    i = 0; // 여기서 0으로 만든 뒤, 주변 바이트 확인
    printf("bytes: ");
    for (int k=0; k<12; k++) {
        printf("%u ", p[k]);
    }
    printf("\n");

    // 원래 네 루프
    printf("dummy: ");
    for (int t=0; t<5; t++) {
        printf("%u ", (unsigned char)ary_a[t]); // UB 포함
    }
    printf("\n");
    return 0;
}