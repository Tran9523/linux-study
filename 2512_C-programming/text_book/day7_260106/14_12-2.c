#include <stdio.h>

//12-2.c - scanf("%s", a) 문자열 받을땐 &가 안 들어감!!
//100개 포인터를 선언해도 같은 주소를 바라봄(현재 값은 banana 들어가서 그렇지 동일)
int main(void)
{
    char *dessert = "apple";    // apple 이 저장된 주소값을
    char *dessert_2nd = "apple";
    char *dessert_3rd = "apple";

    printf("오늘 후식은 %s입니다.\n", dessert); // %s 는 주소를 주면 알아서 널 만날때까지 읽음
    dessert = "banana";
    printf("내일 후식은 %s입니다.\n", dessert); // u나 p로 주소값도 확인 가능

    while (*dessert != '\0'){
        putchar(*dessert);
        dessert++;  // 표현 주의 (dessert + 1) [ * & ]없음
    }                               // 실제로도 같게 출력됨
    printf("\n");
    printf("내일 후식은 %p입니다.\n", dessert);
    printf("내일 후식은 %p입니다.\n", dessert_2nd);
    printf("내일 후식은 %p입니다.\n", dessert_3rd);

    return 0;
}