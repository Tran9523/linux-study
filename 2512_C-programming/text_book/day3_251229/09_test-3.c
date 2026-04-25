#include <stdio.h>

// 교수 수식_배터리 효율
int main(void)
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