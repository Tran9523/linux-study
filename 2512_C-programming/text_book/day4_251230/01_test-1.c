#include <stdio.h>
#include <math.h>

// 최대 견인력과 등판 가능 경사각_mine
double clip(double x, int min, int max);
#define PI 3.141592

int main(void)
{
    int Number;
    double mass, torque, G, eta, r, c, SF;

    printf("총 질량 [kg]: "); if (scanf("%lf", &mass) != 1) return 1;
    printf("모터 정격토크 [Nm]: "); if (scanf("%lf", &torque) != 1) return 1;
    printf("구동 모터 수: "); if (scanf("%d", &Number) != 1) return 1;
    printf("감속비: "); if (scanf("%lf", &G) != 1) return 1;
    printf("구동 효율 eta (90%% == 0.9로 입력): "); if (scanf("%lf", &eta) != 1) return 1;
    printf("바퀴 반지름 [m]: "); if (scanf("%lf", &r) != 1) return 1;
    printf("구름 계수 (예:0.015-0.03): "); if (scanf("%lf", &c) != 1) return 1;
    printf("안전 계수 (>=1): "); if (scanf("%lf", &SF) != 1) return 1;

    double g = 9.81; // 중력 상수
    double T_total = Number * torque * G * eta;
    double F_avail = T_total / r;
    double mg = mass * g;

    double sin_theta = clip(((F_avail / SF - c *mg) / mg), 0, 1);
    double F_need = mg * sin_theta + c*mg;
    double theta_rad = asin(sin_theta);
    double theta_deg = theta_rad * 180.0 / PI;
    double grade = tan(theta_rad) * 100.0;

    printf("기대 결과\n");
    printf("가용 견인력 = %.2lf\n", F_avail);
    printf("max = %.2lf\n", theta_deg);
    printf("등판율 = %.1lf%%\n", grade);

    /* 테스트용
    double sin_theta = (F_avail / SF - c * mg) / mg;
        if (sin_theta < 0.0) sin_theta = 0.0;
        if (sin_theta > 1.0) sin_theta = 1.0;

    const double F_need = mg * sin() + c * mg;
    const double max = clip( ((F_avail/SF) - c * mg)/mg, 0, 1);
    const double grade = tax(max) * 100;
    */
   return 0;
}

double clip(double x, int min, int max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
