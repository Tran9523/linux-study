#include <stdio.h>

int main(void)
{
    int ary[5][6] = { 0 };
    int i, j;
    int num = 1;
    int total = 0;

    // 1~20 초기화 (0~3행, 0~4열)
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            ary[i][j] = num++;
        }
    }

    // 각 행의 합 → 마지막 열 (열 5)
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            ary[i][5] += ary[i][j];
        }
    }

    // 각 열의 합 → 마지막 행 (행 4)
    for (j = 0; j < 5; j++)
    {
        for (i = 0; i < 4; i++)
        {
            ary[4][j] += ary[i][j];
        }
    }

    // 전체 합 → (4,5)
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            total += ary[i][j];
        }
    }
    ary[4][5] = total;

    // 배열 출력
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 6; j++)
        {
            printf("%4d", ary[i][j]);
        }
        printf("\n");
    }

    // 전체 합 출력
    printf("\n1부터 20까지의 합 : %d\n", ary[4][5]);

    return 0;
}