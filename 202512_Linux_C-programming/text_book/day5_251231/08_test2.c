#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// 1. 10개 직접 입력
// 2. 100개 난수 입력
// 3. 증감 방향성 고정 (10회 이상)
// 4. 범위를 20까지 제한
// 1~4 방식
int main(void)
{
    srand((unsigned)time(NULL));

    int su_ac = 0, su_de = 0, event = 0;       // 급가속 및 급감속 카운트 + 변동 확인용 event 추가
    int delta, i;
    int count, range;       // count는 뽑을 수 저장, range는 난수의 범위
    int speed[500] = {0};
    int step;               // 방향성 적당히 조정 위해
    int point, dir, random;              // 분기 설정

    count = sizeof(speed) / sizeof(speed[0]);
    range = 200;
    step = 20;

    speed[0] = rand() % (step * 2);
    speed[1] = speed[0] + (rand() % (step*2) - step);
    point = 9;
    dir = (speed[1] >= speed[0]) ? 1 : -1;
    if (speed[1] < 0) {
        speed[1] = 0;
        dir = 1;
    }
    printf("%5d\t%5d\t", speed[0], speed[1]);

    for (i = 2; i < count; i++) {
        int random = 1 + rand() % step;
        if (point > 0) {
            speed[i] = speed[i-1] + (dir * random);
            point--;
            if (speed[i] < 0) {
                speed[i] = 0;
                event++;
                dir = 1;
                point = 9;
            } 
        } else {
            speed[i] = speed[i-1] + (rand() % (step*2) - step);
            if (speed[i] < 0) {
                speed[i] = 0;
                event++;
                dir = 1;
                point = 9;
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

    printf("\n\n총 변동 횟수: %d\n", event);
    printf("급가속 횟수: %d\n", su_ac);
    printf("급감속 횟수: %d\n", su_de);

    return 0;
}