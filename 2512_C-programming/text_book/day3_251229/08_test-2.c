#include <stdio.h>

// 이동로봇의 배터리 용량 선정_Mine
int main(void)
{
    double I_load, vel, R, V, C, eta;
    double E_usable, P, t, d;   // 사용 가능 에너지, 소비전력(W), 런타임(h), 주행거리(km)
    double spec3, spec4; // 3~4시간 런타임을 위한 용량

    printf("-----사전 선정 정보-----\n");
    printf("평균 전류(A): "); // 부하측
    scanf("%lf", &I_load);      // if (scanf("%lf", &I_load) != 1) return 1;
    printf("평균 속도(km/h): ");
    scanf("%lf", &vel);
    printf("예비율 (20%% == 0.2로 입력): ");
    scanf("%lf", &R);
    printf("-----배터리 정보-----\n");
    printf("공칭전압(V): ");
    scanf("%lf", &V);
    printf("용량 [Ah]: ");
    scanf("%lf", &C);
    printf("시스템 효율 (90%% == 0.9로 입력): ");
    scanf("%lf", &eta);

    E_usable = V * C * eta * (1-R);
    P = V * I_load * 2;  // eta가 중복 적용되는 느낌이라 제거 (기존 = / eta) + 모터 2개 가정
    t = E_usable / P;
    d = vel * t;

    spec3 = 3 * P / ( eta * (1 - R));  // 추후 런타임도 변수 선언
    spec4 = 4 * P / ( eta * (1 - R));  // Wh에 가까운 느낌이라 V를 나눠야 됨(이라고 gpt)

    printf("-----------------------\n");
    printf("사용 가능 에너지 : %.2lf [Wh]\n", E_usable);
    printf("소비 전력 : %.2lf [W]\n", P);       // 모터 2개 가정
    printf("예상 런타임 : %.2lf [h]\n", t);
    printf("예상 주행 거리 : %.2lf [km]\n", d);
    printf("-----------------------\n");
    printf("3~4시간 런타임을 위한 배터리 용량 : %.2lf ~ %.2lf [Ah]\n", spec3, spec4);

    return 0;       // 정상일 때 0, 비정상일 때는 1 뽑고 종료
}