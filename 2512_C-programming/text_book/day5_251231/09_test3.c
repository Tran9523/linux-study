#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 4_my code 스텝 범위를 20으로 제한
int main(void)
{
    srand((unsigned)time(NULL));

    int su_ac = 0, su_de = 0, event = 0;       // 급가속 및 급감속 카운트 + 변동 확인용 event 추가
    int delta, i, count;    // count는 뽑을 수 저장, range는 난수의 범위
    int speed[500] = {0};
    int step;               // 방향성 적당히 조정 위해
    int point, dir, random;              // 분기 설정


    count = sizeof(speed) / sizeof(speed[0]);
    step = 20;

    speed[0] = rand() % (step * 2) + 1;
    speed[1] = speed[0] + (rand() % (step*2) - step);
    point = 9;
    dir = (speed[1] >= speed[0]) ? 1 : -1;
    if (speed[1] <= 0) {
        printf("%5d\t %5d", speed[0], 0);
        printf("\n속도가 0이 되어 종료\n");
        return 0;
    }
    printf("%5d\t%5d\t", speed[0], speed[1]);

    for (i = 2; i < count; i++) {
        random = rand() % step + 1;
        if (point > 0) {
            speed[i] = speed[i-1] + (dir * random);
            point--;
            if (speed[i] <= 0) {
                printf("%5d", 0);
                printf("\n속도가 0이 되어 종료\n");
                break;
            } 
        } else {
            speed[i] = speed[i-1] + (rand() % (step*2) - step);
            if (speed[i] <= 0) {
                printf("%5d", 0);
                printf("\n속도가 0이 되어 종료\n");
                break;
            } 
            switch (dir) {
                case 1:
                    if (speed[i] < speed[i-1]) {
                        dir = -1;
                        point = 9;
                        event++;
                    }
                    break;
                case -1:
                    if (speed[i] > speed[i-1]) {
                        dir = 1;
                        point = 9;
                        event++;
                    }
                    break;
                default:
                    return 1;
            }
        }
    printf("%5d\t", speed[i]);

    }

    for (i = 1; i < count; i++) {
        delta = speed[i] - speed[i-1];
        if (delta >= 10) su_ac++;
        if (delta <= -10) su_de++;
    }

    printf("\n총 변동 횟수: %d\n", event);
    printf("급가속 횟수: %d\n", su_ac);
    printf("급감속 횟수: %d\n", su_de);

    return 0;
}