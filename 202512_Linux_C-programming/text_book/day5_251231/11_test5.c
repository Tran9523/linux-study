#include <stdio.h>
//히스테리시스 경보 시스템 구현 (보니까 첫줄 복붙이라 속도 로그 라고 잘못 씀)
int main(void)
{
    int N, i;
    double battery[100];
    int warning = 0; // 0 : Off, 1 : On

    printf("속도 로그 개수 입력: ");
    scanf("%d", &N);
    printf("배터리 잔량 입력 (%%단위)\n");

    for(i=0; i< N; i++) {
    printf("%d번째 잔량 (%%단위): ", i+1);
    if (scanf("%lf", &battery[i]) != 1) {
        printf("입력 오류\n");
        return 1;
    };

    switch(warning) {
        case 0:
            if( battery[i] <= 30.0) {
                warning = 1;
                printf("경고 ON: 배터리 부족\t\t현재 잔량: '%.2lf%%'\n", battery[i]);
                break;
            } else {
                printf("경고 OFF\t\t현재 잔량: '%.2lf%%'\n", battery[i]);
                break;
            }
        case 1:
            if( battery[i] >= 35.0) {
                warning = 0;
                printf("경고 OFF\t\t현재 잔량: '%.2lf%%'\n", battery[i]);
                break;
            } else {
                printf("경고 ON: 배터리 부족\t\t현재 잔량: '%.2lf%%'\n", battery[i]);
                break;
            }
        default:
            break;
        }

    }

    return 0;
}