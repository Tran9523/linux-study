#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    int* prime;
    int i, j;
    int count = 0;

    printf("양수 입력 : ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("2 이상의 수를 입력하세요.\n");
        return 0;
    }

    // 1️ 동적 할당
    prime = (int*)malloc((n + 1) * sizeof(int));
    if (prime == NULL)
    {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // 2️ 초기화 (모두 소수라고 가정)
    for (i = 0; i <= n; i++)
    {
        prime[i] = 1;
    }
    prime[0] = prime[1] = 0;

    // 3️ 소수 판별 (에라토스테네스의 체)
    for (i = 2; i * i <= n; i++)
    {
        if (prime[i])
        {
            for (j = i * i; j <= n; j += i)
            {
                prime[j] = 0;
            }
        }
    }

    // 4️ 출력 (2부터 시작, 한 줄에 5개)
    for (i = 2; i <= n; i++)
    {
        if (prime[i])
            printf("%4d", i);
        else
            printf("%4c", 'X');

        count++;
        if (count % 5 == 0)
            printf("\n");
    }

    // 줄 끝 정리
    if (count % 5 != 0)
        printf("\n");

    // 5️ 메모리 해제
    free(prime);

    return 0;
}