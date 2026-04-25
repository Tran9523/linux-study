#include <stdio.h>

//11-4.연속 출력(버퍼 이해)
int main(void)
{
    char ch;
    int i;
                    
    for (i = 0; i < 5; i++) {
        scanf("%c", &ch);       // 버퍼에 대기하고 있는 얘를 바로 데려옴(그래서 입력 1번만)
        printf("%c", ch);
    }
    for (i = 0; i < 3; i++) {   // 하나 더 해서 4,5 테스트 - 678 출력되고 뒤에서는 8 중복
        scanf("%c", &ch);
        printf("%c", ch);
    }
    printf("%c", ch);       // 이러면 5번째 나왔던 문자가 중복해서 출력됨 for 하나 더 쓰면 8
    printf("\n");
    return 0;
}
//  i < 7 했을때 tiger
//              tiger
//              234
//              2