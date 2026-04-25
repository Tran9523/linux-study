#include <stdio.h>
#include <math.h>

// 실행할때 Ctrl+Alt+'N' 이 아니라 terminal에서 "gcc day3.c -o day3 S-lm" 입력
int main(void)
{
    double x, y;

    printf("실수 x 입력: ");
    if (scanf("%lf", &x) != 1) return 1;
    printf("실수 y 입력 : ");
    if (scanf("%lf", &y) != 1) return 1;

    printf("\n [math.h 함수 예제]\n");
    printf("sqrt(x) = %.4f\n", sqrt(x));
    printf("pow(x, y) = %.4f\n", pow(x, y));
    printf("sin(x) = %.4f\n", sin(x));
    printf("cos(x) = %.4f\n", cos(x));
    printf("log(x) = %.4f\n", log(x));
    printf("fabs(x) = %.4f\n", fabs(x));

    return 0;
}

/*
// 교수 수식
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


// 이동로봇의 모터 적정성 여부 판단
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


// 5-5.c
int main(void)
{
    int a = 10, b = 20;

    if (a < 0)
    {
        if (b > 0)
        {
            printf("ok1\n");
        }
    }
    else
    {
        printf("ok2\n");
    }

    return 0;
}

// 5-4.c
int main(void)
{
    int a = 20, b = 10;

    if ( a > 10)
    {
        if ( b >= 0)
        {
            b = 1;
        }
        else{
            b = -1;
        }
    }

    printf("a = %d, b = %d\n", a, b);
    return 0;
}

// 4-14.c
int main(void)
{
    int a = 10, b = 5;
    int res;

    res = a / b * 2;
    printf("res = %d\n", res);
    res = ++a * 3;
    printf("res = %d\n", res);
    res = a > b && a != 5;
    printf("res = %d\n", res);
    res = a % 3 == 0;
    printf("res = %d\n", res);

    return 0;
}


// 4-13.c
int main(void)
{
    int a = 10; // 비트열 00000000 00000000 00000000 00001010
    int b = 12; // 비트열 00000000 00000000 00000000 00001100

    printf("a & b : %d\n", a & b);
    printf("a ^ b : %d\n", a ^ b);
    printf("a | b : %d\n", a | b);
    printf("~a : %d\n", ~a);
    printf("a << 1 : %d\n", a << 1);        // 앞의 0은 버려지고 뒤에는 0으로 채워짐
    printf("a >> 2 : %d\n", a >> 2);        // 8421 이라는 코드 (사실상 2진수)

    return 0;
}



// 예제 4-12.c
int main(void)
{
    int a = 40, b = 20, res;

    res = (a > b) ? a*2-b : a+b;
    printf("큰 값 : %d\n", res);

    return 0;
}


// 예제 4-10.c
int main(void)
{
    int a = 10, b= 20;
    int res = 2;

    a += 20;
    res *= b + 10;

    printf("a = %d, b = %d\n", a, b);
    printf("res = %d\n", res);

    return 0;
}
    */