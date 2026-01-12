//여태까지 했던 실습들을 하나의 프로그램으로 만들자!(종합 계산기 -> 바퀴별 속도, 배터리 사용시간, 모터토크, 센서 정규화, 오차율 계산 등등)
//malloc 사용해서 필요한 데이터만 뽑고 반납하고, 불필요한 데이터 사용이 최소화 되도록
//이거는 어중간하게 손 대면 더 답이 없음. 차라리 처음부터 끝까지 직접 쓰는 식으로 해야 될듯 (즉 미완)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    double left;
    double right;
} WheelSpeed;

typedef struct {
    double linear;  
    double angular;
} RobotSpeed;

int robots_speed(void);
RobotSpeed computeSpeed(WheelSpeed w, double w_rad, double w_dist);
void move(Position *p, int dx, int dy);
int move_value(int *a, int *b);
int robot_moves(void);
int lidar_rand(void);
int IR_cal(void);
int hysteresis(void);
int robots_battery(void);
int robots_moter(void);

int main(void){
    int x;

    while (1) {
    printf("\n=== Robot Toolbox ===\n");
    printf("0. 종료\n");
    printf("1. 모터 적정성\n");
    printf("2. 배터리 용량\n");
    printf("3. 히스테리시스\n");
    printf("4. IR 센서\n");
    printf("5. LiDAR 랜덤\n");
    printf("6. 로봇 이동\n");
    printf("7. 속도 계산\n");
    printf("선택: ");

    if (scanf("%d", &x) != 1) {
        printf("숫자만 입력하세요.\n");
        // clear_stdin(); (있으면 호출)
        continue;
    }

    if (x == 0) break;

    switch (x) {
        case 1: robots_moter(); break;
        case 2: robots_battery(); break;
        case 3: hysteresis(); break;
        case 4: IR_cal(); break;
        case 5: lidar_rand(); break;
        case 6: robot_moves(); break;
        case 7: robots_speed(); break;
        default: printf("없는 메뉴입니다.\n"); break;
    }
}

    return 0;
}

// 차동구동 로봇 속도 계산
int robots_speed(void)
{
    WheelSpeed w = {0.0, 0.0};
    RobotSpeed r = {0.0, 0.0};
    double w_rad, w_dist;

    printf("좌우측 바퀴의 속도[rad/s]: ");
    scanf("%lf%lf", &w.left, &w.right);

    printf("바퀴 반지름[m]: ");
    scanf("%lf", &w_rad);
    printf("바퀴 간 거리[m]: ");
    scanf("%lf", &w_dist);

    r = computeSpeed(w, w_rad, w_dist);     //반환하는 형태를 main함수에서 저장하기 위한 구조

    printf("선속도: %.2lf m/s\n", r.linear);
    printf("각속도: %.2lf rad/s\n", r.angular);

    return 0;
}

RobotSpeed computeSpeed(WheelSpeed w, double w_rad, double w_dist)
{
    RobotSpeed r;

    r.linear  = w_rad * (w.left + w.right) / 2.0;
    r.angular = w_rad * (w.right - w.left) / w_dist;

    return r;
}

//로봇 이동 계산 하기(by 함수)

int robot_moves(void)
{
    int a, b;
    Position robot = {0, 0};

    printf("1회 이동\n");
    if (move_value(&a, &b)) move(&robot, a, b);

    printf("2회 이동\n");
    if (move_value(&a, &b)) move(&robot, a, b);
    
    printf("로봇 최종 위치: [%d / %d]\n", robot.x, robot.y);

    return 0;
}

void move(Position *p, int dx, int dy)
{
    p->x += dx;
    p->y += dy;
}

int move_value(int *a, int *b)
{
    printf("위치 이동할 값을 입력하세요[x, y]: ");
    if (scanf("%d%d", a, b) != 2) {
        printf("입력 오류\n");
        return 0;
    }
    return 1;

}

int lidar_rand(void)
{  
    srand(time(NULL));

    int i, min_index, dist = 0;
    int data = 3600;
    int min_value = 501;
    int step = 10, size = 10;

    int *pi = (int *)calloc(size, sizeof(int));
    //pi = (int *)malloc(sizeof(int) * data);
    if (pi == NULL) {
        printf("메모리가 부족합니다.\n");
        exit(1);
    }

    for (i = 0; i < data; i++) {
        if (i >= size) {
            size += step;
            int *tmp = realloc(pi, size * sizeof(int));
            if (!tmp) {
                free(pi);
                printf("메모리가 부족합니다\n");
                exit(1);
            }
            pi = tmp;
        }
        dist = rand() % 501;
        pi[i] = dist;
        if (dist < min_value) {
            min_value = dist;
            min_index = i % 360;
        }
    }

    printf("가장 가까운 거리(cm): %d\n", min_value);
    printf("가장 가까운 거리의 방향(deg): %d\n", min_index);
    
    free(pi);
    
    return 0;
}
// 나의 IR 코드 - 임계 값 기준으로 cnt
int IR_cal(void)
{
    int i, N, threshold;
    int label[15] = {0};
    int black_count = 0, white_count = 0;
    int value[15] = {0};
    double index_avg;

    printf("센서 개수 입력: ");
    scanf("%d", &N);
    printf("센서 값 입력(value): ");
    for ( i = 0; i < N; i++) {
        scanf("%d", &value[i]);
    }
    printf("\n임계값 입력: ");
    scanf("%d", &threshold);

    for (i = 0; i < N; i++) {
        if(value[i] >= threshold) {
            label[i] = 0;
            black_count++;
        } else {
            label[i] = 1;
            white_count++;
        }
        index_avg += i * label[i];
    }

    if (black_count <= 0) {
        index_avg = 0.0;
    } else {
        index_avg = index_avg / black_count;
    }

    printf("label = ");
    for(i < 0; i = N; i++) {
        printf("%2d", label[i]);
    }
    printf("\nblack count = %d", black_count);
    if (black_count <= 0) {
        printf("라인 없음");
    } else {
        printf("index_avg = %lf\n", index_avg);
    }

}
//히스테리시스 경보 시스템 구현 (보니까 첫줄 복붙이라 속도 로그 라고 잘못 씀)
int hysteresis(void)
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

//로봇 배터리 용량 적정성 여부
int robots_battery(void)
{
    double I_load, vel, R, V, C, eta;

    printf("평균 전류 I_load [A] (부하측): "); if (scanf("%lf", &I_load) != 1) return 1;
    printf("평균 속도 vel [km/h]: "); if (scanf("%lf", &vel) != 1) return 1;
    printf("예비율 R (20%% == 0.2로 입력): "); if (scanf("%lf", &R) != 1) return 1;
    printf("공칭전압 V [V]: "); if (scanf("%lf", &V) != 1) return 1;
    printf("용량 C [Ah]: "); if (scanf("%lf", &C) != 1) return 1;
    printf("시스템 효율 eta (90%% == 0.9로 입력): "); if (scanf("%lf", &eta) != 1) return 1;

    if (V <= 0 || C <= 0 || I_load <= 0 || eta <= 0 || eta > 1 || R < 0 || R >= 1) {
        printf("입력값 범위를 확인하세요.\n");
        return 1;
    }   // 입력값 검증

    const double P = (V * I_load) / eta;
    const double E_usable = V * C * eta * (1 - R);
    const double t_h = E_usable / P;
    const double t_min = t_h * 60.0;
    const double d_km = vel * t_h;
    
    printf("-----------------------\n");
    printf("사용 가능 에너지 : %.2lf [Wh]\n", E_usable);
    printf("소비 전력 : %.2lf [W]\n", P);
    printf("예상 런타임 : %.2lf [h] (%.1f min)\n", t_h, t_min);
    printf("예상 주행 거리 : %.2lf [km]\n", d_km);
    printf("-----------------------\n");

    return 0;
}
//이동 로봇의 모터 적정성 여부
int robots_moter(void)
{
    int N;
    double SF, DM;
    double m, R, t, G, W;
    const double c = 0.018, g = 9.81;
    double Fmin, Fmotor;

    printf("-----이동로봇 설계 사양-----\n");
    printf("총 하중(kg) : ");
    scanf("%lf", &m);
    printf("구동 바퀴 수 : ");
    scanf("%d", &N);
    printf("안전 계수 : ");
    scanf("%lf", &SF);
    printf("설계 마진 (20%% == 1.2로 입력) : ");
    scanf("%lf", &DM);
    printf("-----모터 및 바퀴 사양-----\n");
    printf("모터 정격 토크(Nm) : ");
    scanf("%lf", &t);
    printf("감속비 : ");
    scanf("%lf", &G);
    printf("바퀴 반지름(m) : ");
    scanf("%lf", &R);

    W = m * g;
    Fmin = c * W * SF * DM;
    Fmotor = ((t * G) / R) * N;

    printf("----------------------------\n");
    printf("필요한 최소 견인력 : %.2lf [N]\n", Fmin);
    printf("모터가 낼 수 있는 견인력 : %.2lf [N]\n", Fmotor);
    printf("----------------------------\n");
    
    if (Fmin <= Fmotor) {
        if (Fmotor >= Fmin * 1.2) {
            printf("판정 : 만족 (모터의 성능이 과다하게 뛰어납니다.)\n");
        } else if (Fmotor >= Fmin * 1.05) {
            printf("판정 : 만족 (현재 모터로도 충분합니다.)\n");
        } else {
            printf("판정 : 만족 (다만 모터의 성능 마진이 다소 불안합니다.)\n");
        }
    } else {
        printf("판정 : 불만족 (더 큰 모터나 감속비가 필요합니다.)\n");
    }
    
    return 0;
}