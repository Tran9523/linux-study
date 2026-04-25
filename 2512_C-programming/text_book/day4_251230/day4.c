#include <stdio.h>

// 8-1.c
int main(void)
{
    int ary[5];

    ary[0] = 10;
    ary[1] = 20;
    ary[2] = ary[0] + ary[1];
    scanf("%d", &ary[3]);

    printf("%d\n", ary[2]);
    printf("%d\n", ary[3]);
    printf("%d\n", ary[4]);

    return 0;
}


/*
int get_num(void);

int main(void)
{
    int i;
    int result[10];

    for (i = 0; i < 10; i++) {
        result[i] = get_num();
    }

    for (i = 0; i < 10; i++) {
        printf("%d번째 반환값 : %d\n", i + 1, result[i]);
    }
    return 0;
}

int get_num(void)
{
    int num;

    printf("양수 입력: ");
    scanf("%d", &num);

    return num;
}

// degree(각도) 와 radian(파이)을 변환하는 함수
#define PI 3.141592
double change(int, double);

int main(void)
{
    int a;
    double b;
    double result;

    printf("1. Degree -> Radian\n");
    printf("2. Radian -> Degree\n");
    printf("변환할 형식과 변환할 값을 입력하세요.");
    if (scanf("%d %lf", &a, &b) != 2) {
        printf("입력 형식이 올바르지 않습니다.\n");
        return 1;
    }

    result = change(a, b);

    if(a == 1) {
        printf("%.2lf Degree -> %.2lf Radian\n", b, result);
    } else if (a == 2) {
        printf("%.2lf Radian -> %.2lf Degree\n", b, result);
    } else {
        printf("변환 값을 잘못 입력하였습니다.\n");
        return 1;
    }
    
    return 0;
}

double change(int a, double b)
{
    switch(a) {
        case 1: return b * PI / 180.0;
        case 2: return b * 180.0 / PI;
    }

    return 0.0;
}

// test 두 수 의 평균을 구하는 코드 - main & avg
double avg(int x, int y);

int main(void)
{
    int a, b;

    printf("두 수를 입력하세요: ");
    scanf("%d %d", &a, &b);

    printf("두 수의 평균은 %.1lf 입니다.\n", avg(a,b));

    return 0;
}

double avg(int x, int y)
{
    double res;

    res = (x + y) / 2.0;
    return res;
}

// 7-1.c
int sum(int x, int y)
{
    int temp;

    temp = x + y;

    return temp;
}

int main(void)
{
    int a = 10, b = 20;
    int result;

    result = sum(a, b);
    printf("result : %d\n", result);

    return 0;
}

// test 문제 별 찍기
int main(void)
{
    int i, j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if( (i == j) || ( (i + j) == 4))
            {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}

// 6-5.c
int main(void)
{
    int i;
    int sum = 0;

    for (i = 1; i <= 10; i++)
    {
        sum += i;
        if (sum > 30) break;
    }
    printf("누적한 값: %d\n", sum);
    printf("마지막으로 더한 값: %d\n", i);

    return 0;
}

// 구구단 출력
int main(void)
{
    int i, j;
    int temp;

    for ( i = 1 ; i < 9; i++) {
        printf("%d단:", (i+1));
        for ( j = 0; j < 9; j++) {
            temp = (i + 1) * (j + 1);
            printf("%3d", temp);
        }
        printf("\n");
    }
    return 0;
}

// 6-3.c
int main(void)
{
    int a = 1;
    
    do
    {
        a *= 2;
    } while (a < 10);
    printf("a : %d\n", a);

    return 0;    
}       // a : 16

//  여기서부터 끊기
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

// 최대 견인력과 등판 가능 경사각
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

    // 테스트용
    double sin_theta = (F_avail / SF - c * mg) / mg;
        if (sin_theta < 0.0) sin_theta = 0.0;
        if (sin_theta > 1.0) sin_theta = 1.0;

    const double F_need = mg * sin(?) + c * mg;
    const double max = clip( ((F_avail/SF) - c * mg)/mg, 0, 1);
    const double grade = tax(max) * 100;
    
   return 0;
}

double clip(double x, int min, int max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

*/