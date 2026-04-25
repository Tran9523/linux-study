#include <stdio.h>
//14-4.c 함수 초기화 할때 "123"로 넣으면 뒤에 널 / 하나하나('a' 'b') 하면 마지막 널 넣어주기
int main(void)
{
    char animal1[5][10] = {
        {'d','o','g','1','\0'},
        {'d','o','g','2','\0'},
        {'d','o','g','3','\0'},
        {'d','o','g','4','\0'},
        {'d','o','g','5','\0'}
    };

    char animal2[][10] = { "dog", "tiger", "rabbit", "horse", "cat"};
    int i;
    for (i = 0; i < 5; i++) {
        printf("%s\t", animal1[i]);
    }
    printf("\n");
    for (i = 0; i < 5; i++) {
        printf("%s\t", animal2[i]);
    }

    return 0;
}