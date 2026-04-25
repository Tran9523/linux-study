#include <stdio.h>

//test 문제 - Bonus : data print
//각 달의 인수를 저장한 배열, Month[0]은 1월, Month 값을 한줄에 5개씩 출력
void print_month(int *mp);
void print_day(int *mp);

int main(void)
{
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    print_month(month);
    print_day(month);

    return 0;
}

void print_month(int *mp)
{
    int i, cnt = 0;

    for (i = 0; i < 12; i++) {              //각 달의 일수 출력
        if ((cnt % 5) == 0) printf("\n");      // 출력 개수가 5의 배수라면 줄 바꿈
        printf("%5d", mp[i]);
        cnt++;
    }
    printf("\n");
}

void print_day(int *mp)         //연습용 - gpt 도움받기
{
    int month, i;

    printf("\n출력할 달을 입력하세요 (1~12): ");
    scanf("%d", &month);

    if (month < 1 || month > 12) {
        printf("잘못된 달 입력입니다.\n");
        return;
    }

    printf("[%d월]\n", month);

    for (i = 1; i <= mp[month - 1]; i++) {
        printf("%2d ", i);

        if (i % 7 == 0)   // 7개 단위 줄바꿈
            printf("\n");
    }
    printf("\n");
}