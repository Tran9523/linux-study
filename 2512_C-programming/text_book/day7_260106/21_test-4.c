#include <stdio.h>
#include <string.h>

// + scanf / gets / fgets - 개항 포함?
// + puts / fputs - 개행문과 처리 하는 방법 리뷰
// 다음 프로그램의 문제를 찾고 코드 추가 삭제 바르게 실행 (버퍼의 이해)
int main(void)
{
    char ani[20];
    char why[80];
    printf("좋아하는 동물 : ");
    //fgets(ani, sizeof(ani), stdin);       // 2. 예시에서 이거 수정
    //ani[strlen(ani) -1] = '\0';           // 2. 개행문자 처리하고 혹은 아래 fgets 수정
    scanf("%s", ani);
    printf("좋아하는 이유 : ");
    //getchar();      //  1. 예시에서 추가하면 끝
    //fgets(why, sizeof(why), stdin);
    //scanf("%s", why);         // 이건 공백을 받을 수 없어서 "%[^\n]" 식으로 바꿔야
    printf("%s is %s", ani, why);
    //printf("print: %d", why[0]); - 개행 문자 포함이라 예시 그대로 가면 10 나옴

    return 0;
}
// 결과 예시
// 좋아하는 동물 : dog
// 좋아하는 이유 : very faithhul
// dog is very faithful