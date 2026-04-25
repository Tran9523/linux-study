#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 5. 무한 반복 = 속도가 0이 되면 종료 - 배열로는 불가능이라 gpt로 변경
int main(void)
{
    srand((unsigned)time(NULL));

    int su_ac = 0, su_de = 0, event = 0;
    int prev, cur;
    int delta;

    int step = 20;
    int dir;
    int point;

    const int MIN_RUN = 10;   // 최소 유지 횟수

    // 초기값 2개 생성
    prev = rand() % (step * 2) + 1;
    cur  = prev + (rand() % (step * 2) - step);

    if (cur <= 0) {
        printf("%d\t0\n속도가 0이 되어 종료\n", prev);
        return 0;
    }

    dir = (cur >= prev) ? 1 : -1;
    point = MIN_RUN;

    printf("%d\t%d\t", prev, cur);

    // ===== 무한 반복 시작 =====
    while (1) {
        int random = 1 + rand() % step;

        // 다음 값 생성
        int next;
        if (point > 0) {
            next = cur + dir * random;
            point--;
        } else {
            next = cur + (rand() % (step * 2) - step);

            // 우연히 방향이 바뀌었으면 dir 갱신
            if (dir == 1 && next < cur) {
                dir = -1;
                point = MIN_RUN;
                event++;
            } else if (dir == -1 && next > cur) {
                dir = 1;
                point = MIN_RUN;
                event++;
            }
        }

        // 0이면 종료
        if (next <= 0) {
            printf("0\n속도가 0이 되어 종료\n");
            break;
        }

        // 급가속 / 급감속 판단
        delta = next - cur;
        if (delta >= 10) su_ac++;
        else if (delta <= -10) su_de++;

        // 출력
        printf("%d\t", next);

        // 다음 루프 준비
        prev = cur;
        cur  = next;
    }

    printf("\n총 변동 횟수: %d\n", event);
    printf("급가속 횟수: %d\n", su_ac);
    printf("급감속 횟수: %d\n", su_de);

    return 0;
}