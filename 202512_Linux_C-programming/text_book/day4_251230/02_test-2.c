#include <stdio.h>
//  바퀴 왜곡률_mine
#include <math.h>
#define PI 3.141592

int main(void)
{
    double r, W, e_l, e_r, L;

    printf("-----입력 요소-----\n");
    printf("바퀴 반지름 [m]: "); if (scanf("%lf", &r) != 1) return 1;
    printf("트랙 폭 [m]: "); if (scanf("%lf", &W) != 1) return 1;
    printf("좌측 바퀴 오차율 [%%]: "); if (scanf("%lf", &e_l) != 1) return 1;
    printf("우측 바퀴 오차율 [%%]: "); if (scanf("%lf", &e_r) != 1) return 1;
    printf("목표 주행 거리 [m]: "); if (scanf("%lf", &L) != 1) return 1;
    if (e_l == e_r) return 1;

    double w_l = r * (1 + e_l / 100);
    double w_r = r * (1 + e_r / 100);
    double Rc = (W / 2.0) * ((w_l + w_r) / (w_r - w_l));
    double d_rad = L / Rc;
    double d_deg = d_rad * 180.0 / PI;
    double d_drift = Rc * (1.0 - cos(d_rad));

    printf("\n-----출력 요소-----\n");
    printf("좌/우 바퀴 반경 : %.4lf m / %.4lf m\n", w_l, w_r);
    printf("곡률 반경 Rc = %.2lf m\n", Rc);
    printf("편류각 = %.2lf deg\n", d_deg);
    printf("편류거리 d_drift = %.2lf m\n", d_drift);

    return 0;
}