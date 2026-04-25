#include <stdio.h>

// 이동로봇의 모터 적정성 여부 판단, 수식은 제공됨
int main(void)
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