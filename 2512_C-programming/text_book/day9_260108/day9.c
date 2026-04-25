#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//test3 heap에다가 넣기 (1초간 데이터 저장)
#define HZ 10
int main(void)
{  
    srand(time(NULL));

    int i, min_index, dist = 0;
    int data = HZ * 360;
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

/*
//test2 최소 3개 찾기
int main(void)
{  
    srand(time(NULL));

    int i, j;
    int temp1;
    double temp2;
    int min_index[3] = {-1, -1, -1};
    double dist[360];
    double min_value[3] = {500, 500, 500};

    for (i = 0; i < 360; i++) {
        dist[i] = (rand() % 50001) / 100.0;
        if (dist[i] < min_value[2]) {
            min_value[2] = dist[i];
            min_index[2] = i;
            for (j = 2; j > 0; j--) {
                if (min_value[j-1] > min_value[j]) {
                    temp1 = min_index[j-1];
                    min_index[j-1] = min_index[j];
                    min_index[j] = temp1;
                    temp2 = min_value[j-1];
                    min_value[j-1] = min_value[j];
                    min_value[j] = temp2;
                }
            }
        }
    }

    printf("\t[Lidar 최소 거리 Top3]\n");
    printf("가장 가까운 거리(cm): ");
    printf("%.2lf & %.2lf & %.2lf\n", min_value[0], min_value[1], min_value[2]);
    printf("가장 가까운 거리의 방향(deg): ");
    printf("%d & %d & %d\n", min_index[0], min_index[1], min_index[2]);

    return 0;

}

/*
//test1 - 360도 센서 입력된 거리값 중 가장 가까운 거리와방향
//손으로 하면 10~12 / 랜덤 배웠으니까 랜덤 360개(상승폭의 제한 +- 10 or 50?정도)
//방향도 알려주는/ 입력조건 360개
int main(void)
{  
    srand(time(NULL));

    int i, min_index;
    double dist[360];
    double min_value;

    dist[0] = (rand() % 50001) / 100.0;
    min_value = dist[0];
    min_index = 0;
    
    for (i = 1; i < 360; i++) {
        dist[i] = (rand() % 50001) / 100.0;
        if (min_value > dist[i]) {
            min_value = dist[i];
            min_index = i;
        }
    }

    printf("가장 가까운 거리(cm): %.2lf\n", min_value);
    printf("가장 가까운 거리의 방향(deg): %d\n", min_index);

    return 0;

}

/*
//연습문제 5 이건 메모리 관련이라 절대 실행 X
//정답을 굳이 찾자면 (ptr - 5) 가 맞지만, 그래도 원래 주소를 저장하는게 베스트
#include <stdlib.h>

int main(void)
{
    int *ptr = (int *)malloc(sizeof(int) * 5);

    for (int i = 0; i < 5; i++) {
        *ptr = i * 10;
        ptr++;
    }

    free(???);
    return 0;
}
/*
//연습문제 4 5라 결과적으론 맞음 
int main(void)
{
    int arr[2][3] = { {1,2,3}, {4,5,6} };
    int (*p)[3] = arr;
    printf("%d", *(*(p + 1) + 1));

    return 0;
}

/*
//연습문제 3 - 후위니까 10 맞지
int main(void)
{
    int arr[] = {10, 20, 30};
    int *ptr = arr;

    printf("%d", *ptr++);
    return 0;
}

/*
//연습문제 2 (그래도 헷갈림 지피티)
int main(void)
{
    int arr[3] = {10, 20, 30};
    int *p = arr;

    printf("%d\n", ++*p);
    printf("%d\n", *p++);
    printf("%d\n", (*p)++);
    printf("%d\n", *p);

    return 0;
}

/*
//연습문제 1 (48이라 씀 -> 비트 연산 방향 헷갈림)
int main(void)
{
    unsigned char b = 12;
    printf("%d", b >> 2);

    return 0;
}
/*
//16-4.c
#include <string.h>

int main(void)
{
    char temp[80];
    char *str[3];
    int i;

    for (i = 0; i < 3; i++) {
        printf("문자열을 입력하세요: ");
        gets(temp);
        str[i] = (char *)malloc(strlen(temp) + 1);
        strcpy(str[i], temp);
    }
    
    for (i = 0; i < 3; i++) {
        printf("%s\n", str[i]);
    }

    for (i = 0; i < 3; i++) {
        free(str[i]);
    }

    return 0;
}

/*
//16-3.c
int main(void)
{
    int *pi;
    int size = 5;
    int count = 0;
    int num;
    int i;

    pi = (int *)calloc(size, sizeof(int));      // size개 들어갈 공간 만들기
                                //sizeof랑 혼용 X
    while (1) {
        printf("양수만 입력하세요 => ");
        scanf("%d", &num);
        if (num <= 0) break;
        if (count == size) {
            size += 5;
            pi = (int *)realloc(pi, size * sizeof(int));    // realloc 할당 오류 주의
        }                       // 할당 과정에서 주소가 바뀐다고 해도 상관 없이 pi가 따라감
        pi[count++] = num;
    }
    for (i = 0; i < count; i++) {
        printf("%5d", pi[i]);
    }
    free(pi);

    return 0;
}

//16-2.c - 주의 - pi로 주소 지정했다가 다른 주소로 덮어씌웠다? -> malloc 찾을 수 없어서 누수
int main(void)
{
    int *pi;
    int i, sum = 0;

    pi = (int *)malloc(5 * sizeof(int));    // 배열처럼 사용하겠다 - 이 형태 많이 씀
    if (pi == NULL) {
        printf("# 메모리가 부족합니다.\n");
        exit(1);
    }

    printf("다섯 명의 나이를 입력하세요: ");
    for (i = 0; i < 5; i++){
        scanf("%d", &pi[i]);
        sum += pi[i];
    }
    printf("다섯 명의 평균 나이: %.1lf\n", (sum / 5.0));
    free(pi);       // pi 주소를 놓쳐버리면 free로 할당된 영역 못 품

    return 0;
}

/*
//16-1.c '공간을 잡고 있다'표현 유의
//C언어에서는 캐스팅 안해도 된다함 [ pi = malloc(sizeof(int)) ]
int main(void)
{
    int *pi;
    double *pd;
                    //(int *)malloc(4) 와 같음
    pi = (int *)malloc(sizeof(int));    //int의 사이즈(4byte)로 공간배정(heap영역)
    if (pi == NULL) {
        printf("# 메모리가 부족합니다.\n"); //if 백만 배정(연속되야함) - 없으면 NULL 반환
        exit(1);                        //그걸 확인하는 과정
    }

    pd = (double *)malloc(sizeof(double));  // 그럼 여기도 확인해야???
    if (pd == NULL) {
        printf("# 메모리가 부족합니다.\n");
        free(pi);                   // 앞에서 할당한거 정리
        exit(1);
    }

    *pi = 10;       // malloc 할당된 영역은 이름도 없지만 포인터로 사용 가능
    *pd = 3.4;

    printf("int : %d\n", *pi);
    printf("double: %.1lf\n", *pd);

    free(pi);       // 반환 필수 <- 메모리 누수가 발생함
    free(pd);

    return 0;
}


/*
// 이 상단부터는 다 stdlib.h 사용 (동적 할당) - 스탠다드라이브러리
//15-9.c void포인터는 간접 참조 연산고 주소에 대한 정수 연산이 불가능
int main(void)
{
    int a = 10;
    double b = 3.5;
    void *vp;       // 앞에 어떤 형태가 올건지 쓸때마다 알려줘야 됨

    vp = &a;
    printf("a: %d\n", *(int *)vp);

    vp = &b;
    printf("b: %.1lf\n", *(double *)vp);

    return 0;
}
//  a: 10
//  b: 3.5

/*
//15-8.c
void func(int (*fp)(int, int));
int sum(int a, int b);
int mul(int a, int b);
int max(int a, int b);

int main(void)
{
    int sel;

    printf("두 정수의 합 [1]\n");
    printf("두 정수의 곱 [2]\n");
    printf("두 정수 중에서 큰 값 계산 [3]\n");
    printf("원하는 연산을 선택하세요: ");
    scanf("%d", &sel);

    switch (sel) {
        case 1: func(sum); break;
        case 2: func(mul); break;
        case 3: func(max); break;
        default: printf("입력 오류"); break;
    }

    return 0;
}
void func(int (*fp)(int, int))
{
    int a, b;
    int res;
                    //func의 변수로 fp를 줬음 = 기억 
    printf("두 정수의 값을 입력하세요: ");
    scanf("%d %d", &a, &b);
    res = fp(a, b);
    printf("결과값은 [%d]\n", res);
}

int sum(int a, int b)
{
    return (a + b);
}

int mul(int a, int b)
{
    return (a * b);
}

int max(int a, int b)
{
    if (a > b) return a;
    else return b;
}
//  01 두 정수의 합
//  02 두 정수의 곱
//  03 두 정수 중에서 큰 값 계산
//  원하는 연산을 선택하세요: 1
//  두 정수의 값을 입력하세요: 10 15
//  결과값은 [25]

/*
//15-7.c 배열 포인터 = int (*pa)[4];
int sum(int, int);

int main(void)
{
    int (*fp)(int, int);        // 포인터 하나를 선언한게 끝
    int res;

    fp = sum;       // 함수형태를 받는 포인터 (그러면 뒷단이 받는 매개변수)
    res = fp(10, 20);
    printf("result: %d\n", res);

    return 0;
}
int sum(int a, int b)
{
    return (a + b);
}
//  result: 30

/*
//연습 문제
//예상 - a 10 / b 20  - pa 20 / pb 10 [일치함]
int main(void)
{
    int a = 10, b = 20;
    int *pa = &a, *pb = &b;
    int **ppa = &pa, **ppb = &pb;
    int *pt;

    pt = *ppa;
    *ppa = *ppb;
    *ppb = pt;

    printf("a: %d\tb: %d\n", a, b);
    printf("*pa: %d\t*pb: %d\n", *pa, *pb);

    return 0;
}
//  a: 10   b: 20
//  *pa: 20 *pb: 10

/*
//15-6.c
void print_ary(int (*)[4]);     // 열 의미하는 [4] + 여기다가 포인트 형태로 줄꺼야~

int main(void)
{
    int ary[3][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
    print_ary(ary); // 여기서 ary 주면 저기서 그 주소로 받는 그런 느낌인가봄

    return 0;
}
void print_ary(int (*pa)[4])    // 동일 의미 (*pa) = pa[]
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%5d", pa[i][j]);
        }
        printf("\n");
    }
}
//    1    2    3    4
//    5    6    7    8
//    9   10   11   12

/*
//15-5.c
int main(void)
{
    int ary[3][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
    int (*pa)[4];   // 배열 포인터 (int = 4칸씩 끊어읽는 포인터다~)
    int i, j;
    pa = ary;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%5d", pa[i][j]);
        }
        printf("\n");
    }
    return 0;
}
//    1    2    3    4
//    5    6    7    8
//    9   10   11   12

/*
//15-4.c print에 배열명을 넣으면 주소값이다 리마인드
int main(void)
{
    int ary[5];

    printf("ary의 값: %u\t", ary);
    printf("ary의 주소: %u\n", &ary);
    printf("ary + 1: %u\t", ary +1);    // ary[1]
    printf("&ary + 1: %u\n", &ary + 1); // ary 끝난 다음 주소

    return 0;
}
//ary의 값: 3826578560    ary의 주소: 3826578560
//ary + 1: 3826578564    &ary + 1: 3826578580
*/