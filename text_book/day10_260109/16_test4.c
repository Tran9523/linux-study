#include <stdio.h>

// 차동구동 로봇 속도 계산
// 메인에서 왼쪽/오른쪽 바퀴 속도 바퀴 반지름 바퀴 간 기름
// 입력 방어 구조가 있으면 베스트 + 나누기가 들어가니까 0값 방지도 필수
typedef struct {        //좌우 바퀴 속도
    double left;
    double right;
} WheelSpeed;

typedef struct {        //선 속도(앞으로 가는 속도) & 각 속도(돌아가는 속도)
    double linear;  
    double angular;
} RobotSpeed;

RobotSpeed computeSpeed(WheelSpeed w, double w_rad, double w_dist);
// 반환하는 형태가 위의 구조체, 받는 값은 최상단의 구조체

int main(void)
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