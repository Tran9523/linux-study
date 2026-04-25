#include <stdio.h>
//14-7.c 포인터배열
int main(void)
{
    int ary1[4] = {1, 2, 3, 4};
    int ary2[4] = {11, 12, 13};         // 0 초기화 확인
    int ary3[4] = {21, 22, 23, 24};
    int *pary[3] = {ary1, ary2, ary3};      // 선언할 때는 1차원
    int i, j;
    int cnt = 0;
                        // pary[1] = ary1 : ary1[1] -> pary[1][1]
                        // pary[2][2] = *(pary[2] + 2) = *(300 + (2 * sizeof(int)))
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            cnt += pary[i][j];
            printf("%5d", pary[i][j]);      // 붙여쓰지만 하나는 아니다
        }
        printf("\n");
    }
    printf("종합: [%d]\n", cnt);

    return 0;
}