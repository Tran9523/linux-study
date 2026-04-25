#include <stdio.h>
//test 배열 값 계산
//5행6열 2차원 배열을 선언하고 4행 5열은 1~20 으로 초기화
//마지막 열에는 각행의 합, 마지막 행에는 각 열의 합 / 이후 전체 배열의 값
//이후 rows 랑 cols 에 값 넣는 식으로 -> 안됨 동적할당 받아야 되서 어려움
#define ROWS 5
#define COLS 6
#define DATA_ROWS (ROWS -1)
#define DATA_COLS (COLS -1)

int main(void)
{
    int ary[ROWS][COLS] = {0};
    int i, j;
    int cnt = 1;
    int r_total, c_total;

    for (i = 0; i < DATA_ROWS; i++) {
        r_total = 0;
        for (j = 0; j < DATA_COLS; j++) {
            ary[i][j] = cnt;
            r_total += ary[i][j];
            cnt++;
        }
        ary[i][DATA_COLS] = r_total;
    }

    for (j = 0; j < COLS; j++) {
        c_total = 0;
        for (i = 0; i < DATA_ROWS; i++) {
            c_total += ary[i][j];
        }
        ary[DATA_ROWS][j] = c_total;
    }
    printf("   가로세로의 합 구하기\n");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%4d", ary[i][j]);
        }
        printf("\n");
    }
    printf("전체 배열(%d)(%d)의 값: [%d]\n", DATA_ROWS, DATA_COLS, ary[DATA_ROWS][DATA_COLS]);
    return 0;

}