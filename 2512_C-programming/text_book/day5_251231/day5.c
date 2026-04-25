#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

/*
// 1. 10개 직접 입력
// 2. 100개 난수 입력
// 3. 증감 방향성 고정 (10회 이상)
// 4. 범위를 20까지 제한
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

// 4_my code
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

// 랜덤 함수 써보기
int main(void)
{
    srand(time(NULL));  // 랜덤 초기화

    int r1 = rand() % 10; // 0~9사이
    int r2 = rand() % 100 + 1; // 0~99 에서 +1
    int r3 = rand() % 21 - 10; // 20이후 빼기니까 -10 ~ 10 사이
//    int num = rand();  // 0이상 RAND_MAX 이하의 정수 (32767-2bytes & 4bytes)

    printf("0~9 랜덤: %d\n", r1);
    printf("1~100 랜덤: %d\n", r2);
    printf("-10~10 랜덤: %d\n", r3);

    return 0;
}

// 8-7.c
int main(void)
{
    char str[80];

    printf("%s\n", str);

    str[0] = 'O';
    str[1] = 'K';
    fgets(str, sizeof(str), stdin);     // fgets 사용
    printf("%s\n", str);

    return 0;
}

// 8-6.c (gets 는 잘 안 쓰는 추세) - fgets(str, 100 = sizeof(str), stdin) 형식으로
int main(void)
{
    char str[80];

    printf("문자열 입력: ");
    scanf("%s", str);
    // Love is belief... 입력해도 Love 만 (개행문자 저장X & (공백)Love 동일)
    // gets(str); // 메모리랑 상관없이 입력됨(overflow)
    puts("입력된 문자열: ");
    puts(str);

    return 0;
}

// 8-5.c
int main(void)
{
    char str1[80] = "cat";
    char str2[80];

    strcpy(str1, "tiger");
    strcpy(str2, str1);
    printf("%s, %s\n", str1, str2);

    return 0;
}

// 8-4.c
int main(void)
{
    char str[80] = "applejam";  // 초기화 하지 않은 경우 쓰레기 들어감
    //char str[80] = { 'a', 'p','p'};  // 뒤에 널 문자 붙는지 확인용

    printf("최초 문자열: %s\n", str);
    printf("문자열 입력: ");
    scanf("%s", str);  // 문자열은 & 입력X - 남은 문자열은 덮어쓰기라 남아있음
    printf("입력 후 문자열: %s\n", str);
    printf("입력 후 9번째 문자 & ASCII 문자: %c, %d\n", str[8], str[8]);    // str[] = "grape \0 am \0" 인 상태

    return 0;
}

// 8-3.c
int main(void)
{
    int score[5];
    int i;
    int total = 0;
    double avg;
    int count;


    count = sizeof(score) / sizeof(score[0]);

    for (i = 0; i < count; i++)
    {
        scanf("%d", &score[i]);
    }

    for (i = 0; i < count; i++)
    {
        total += score[i];
    }
    avg = total / (double)count;

    for (i = 0; i < count; i++)
    {
        printf("%5d", score[i]);
    }
    printf("\n");

    printf("평균 : %.1lf\n", avg);

    return 0;
}

// 8-2.c
int main(void)
{
    int score[5];
    int i;
    int total = 0;
    double avg;


    for (i=0; i < 5; i++)
    {
        scanf("%d", &score[i]);
    }

    for (i = 0; i < 5; i++)
    {
        total += score[i];
    }
    avg = total / 5.0;

    for (i = 0; i < 5; i++)
    {
        printf("%5d", score[i]);
    }
    printf("\n");

    printf("평균 : %.1lf\n", avg);

    return 0;
}
*/