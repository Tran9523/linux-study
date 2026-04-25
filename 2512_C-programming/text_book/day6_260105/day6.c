#include <stdio.h>

// 왜 3번째 ary가 0으로 나오는지 체크용 gpt 코드
int main(void) {
    int ary[3] = {10,20,30};
    int *pa = ary;
    int i = 12345;              // 일부러 0이 아닌 값으로 시작
    char ary_a[2] = {'a','A'};
    unsigned char *p = (unsigned char*)ary_a;

    printf("&ary_a[0]=%p, &ary_a[1]=%p\n", (void*)&ary_a[0], (void*)&ary_a[1]);
    printf("&i=%p\n", (void*)&i);

    i = 0; // 여기서 0으로 만든 뒤, 주변 바이트 확인
    printf("bytes: ");
    for (int k=0; k<12; k++) {
        printf("%u ", p[k]);
    }
    printf("\n");

    // 원래 네 루프
    printf("dummy: ");
    for (int t=0; t<5; t++) {
        printf("%u ", (unsigned char)ary_a[t]); // UB 포함
    }
    printf("\n");
    return 0;
}
/*
//10-4.c
int main(void)
{
    int ary[5] = {10, 20, 30, 40, 50};  // 여기서 ary[]로도 입력해도 동일
    int *pa = ary;
    int *pb = pa + 3;

    printf("pa : %u\n", pa);
    printf("pb : %u\n", pb);
    pa++;
    printf("pb - pa : %u\n", pb - pa);  // 여기서 2 나오는게 중요(int size가 4임에도)
                                        //  (값 8) / sizeof(int) = 8 / 4 = 2
    printf("앞에 있는 배열 요소의 값 출력: ");
    if (pa < pb) printf("*pa출력 = %d\n", *pa);
    else printf("*pb출력 = %d\n", *pb);

    return 0;
}


//10-3.c
int main(void)
{
    int ary[3] = { 10, 20, 30};
    int *pa = ary;
    int i;
    char ary_a[2] = {'a', 'A'};
    char *pc = ary_a;

    printf("배열의 값과 주소: \n");
    for (i=0; i<3; i++) {
        printf("%d\t", *pa);
        printf("%p\n", pa); //gpt 추천은 %u 보다 %p
        pa++;
    }
    printf("\n더미값 확인\n");
    
    for(i=0; i<5; i++) {
        printf("%d\t", *pc);
        pc++;
    }
    
    return 0;
}


//10-2.c
int main(void)
{
    int ary[3];
    int *pa = ary;
    int i;

    *pa = 10;
    *(pa + 1) = 20;
    pa[2] = pa[0] + pa[1]; // ary = &ary[0] / ary[0] = pa[0]

    for (i = 0; i < 3; i++) 
    printf("%5d", ary[i]);

    return 0;
}

//10-1.c
int main(void)
{
    int ary[3];
    int i;

    *(ary + 0) = 10;
    *(ary + 1) = *(ary + 0) + 10;

    printf("세번째 배열 요소에 키보드 입력: ");
    scanf("%d", ary + 2);

    for (i = 0; i < 3; i++) {
        printf("%5d", *(ary + i));
    }
    printf("\n");
    return 0;

}


//9-9.c 단순 변수는 공유되지 않는다. 증명
void swap(int x, int y);

int main(void)
{
    int a = 10, b = 20;

    swap(a, b);
    printf("a: %d, b: %d\n", a, b);

    return 0;
}

void swap(int x, int y)
{
    int temp;

    temp = x;
    x = y;
    y = temp;
}


//9-8.c (단 수정할 때 포인터를 쓰면 안됨)
void swap(void);
void swap_ary(int ary[]);    //2안 배열을 만들어서 진행 가능
int a = 10, b = 20;     //실제 스왑이 가능하려면 2 함수가 같은 변수를 사용해야...

int main(void)
{
    swap();
    int ary[2] = {10, 20};    //[2]안의 값이 2개라는 소리니까 개수 이해 잘하기
    swap_ary(ary);
    printf("a: %d, b: %d\n", a, b);
    printf("a: %d, b: %d -배열\n", ary[0], ary[1]);

    return 0;
}

void swap(void)
{
    int temp;

    temp = a;
    a = b;
    b = temp;
}

void swap_ary(int ary[])
{
    int temp;

    temp = ary[0];
    ary[0] = ary[1];
    ary[1] = temp;
}


//9-7.c
//함수를 벗어나면 같은 변수가 아님 다르게 적용 = 그래서 포인터를 넣어야 변환 가능
void swap(int *pa, int *pb);
void swap2(int a, int b);

int main(void)
{
    int a = 10, b = 20;

    swap2(a, b);
    printf("a:%d, b:%d\n", a, b);   // 변수가 각각 다르기에 10 20 유지됨

    swap(&a, &b);
    printf("a:%d, b:%d\n", a, b);

    return 0;
}

void swap(int *pa, int *pb)
{
    int temp;

    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void swap2(int a, int b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;

    return;     // 던져줄 값이 2개라 식을 다르게 적어야됨
}


//형변환 테스트
int main(void)
{
    int a = 10;
    int *p = &a;
    double *pd;
//    double *ps;   // 주소 확인용 값 추가1

//    pd = p;             // 기본
//    (int *)pd = p;      // 1번 -- 뒤를 기본 형태로 가면 어쨌든 5~8 번째에서 쓰레기값
    pd = (double *)p;   // 2번 -- 어차피 뒤에서 더블로 읽는 순간 불가능
//    ps = p;       // 주소 확인용 값 추가2

    printf("%lf\n", *pd); // 기본
//    printf("%lf\n", *ps); // 주소 확인용 값 추가3
//    printf("%d\n", *(int *)pd); // 3반 -- * 붙이면 가능 / 형 변환하고 포인터 처리까지
    
    return 0;
}

//9-6.c
// *pd 값이 10이 될 수 있도록 수정 [pd를 int형 + %lf 에서 %d] [double a 선언]
int main(void)
{
    int a = 10;
    //double a = 10;
    int *p = &a;
    double *pd;

    pd = p;     //포인터 p 값을 포인터 pd에 대입
    
    printf("%lf\n", *pd);
    printf("%d\n", *p);
    
    return 0;
}

//9-5.c sizeof 연산자로 변수와 주소의 크기 확인
// 32bit 환경에서는  4 byte  &  64bit 환경에서는 8 byte
int main(void)
{
    char ch;
    int in;
    double db;

    char *pc = &ch;
    int *pi = &in;
    double *pd = &db;

    printf("char형 변수의 주소 크기: %d\n", sizeof(&ch));
    printf("int형 변수의 주소 크기: %d\n", sizeof(&in));
    printf("double형 변수의 주소 크기: %d\n\n", sizeof(&db));

    printf("char * 포인터의 크기: %d\n", sizeof(pc));
    printf("int * 포인터의 크기: %d\n", sizeof(pi));
    printf("double * 포인터의 크기: %d\n\n", sizeof(pd));

    printf("char * 포인터가 가리키는 변수의 크기: %d\n", sizeof(*pc));
    printf("int * 포인터가 가리키는 변수의 크기: %d\n", sizeof(*pi));
    printf("double * 포인터가 가리키는 변수의 크기: %d\n", sizeof(*pd));

    return 0;
}

//9-4.c const int 선언했을때 차이점
int main(void)
{
    int a = 10, b = 20;
    const int *pa = &a;     // pa = 20; (X) a는 pa를 간접 참조하여 바꿀 수 없다(const)
                            // 없으면 *pa = 20; 으로 마지막에 20 출력 가능
    printf("변수 a값: %d\n", *pa);
    pa = &b;
    printf("변수 b값: %d\n", *pa);
    pa = &a;
    printf("주소만 변경했을 때: %d\n", *pa);
    a = 20;
    printf("변수 a값: %d\n", *pa);  // sizeof(pa) = 8, sizeof(*pa) = 4

    return 0;
}

//9-3.c 포인터로 숫자 넣어보기
int main(void)
{
    int a = 10, b = 15, total;
    double avg;
    int *pa, *pb;    // double 로 실행 시 -523383048, 0 등으로 오류
    int *pt = &total;
    double *pg = &avg;

    pa = &a;
    pb = &b;
    *pt = *pa + *pb;
    *pg = *pt / 2.0;

    //*pa = 20;
    //b = 40;

    printf("두 정수의 값: %d, %d\n", *pa, *pb);
    printf("두 정수의 합: %d\n", *pt);
    printf("두 정수의 평균: %.1lf\n", *pg);
    printf("두 정수의 값: %d, %d\n", a, b);
    printf("두 정수의 합: %d\n", total);
    printf("두 정수의 평균: %.1lf\n", avg);

    return 0;
}

//9-2.c 포인터와 변수 주소
int main(void)
{
    int a;  // ex. 100번지에 a
    int *pa;    // ex. 200번지에 *pa - 여기서 int는 가리킬 값, 내가 int라는게 아님

    pa = &a;    // 200번지에 100번지 '주소' 입력 = pa -> a
    *pa = 10;   // 100번지'의 값'에 10 입력

    printf("포인터로 a 값 출력: %d\n", *pa);
    printf("변수명으로 a 값 출력: %d\n", a);

    return 0;
}

//9-1.c 주소 값 확인
int main(void)
{
    int a;
    double b;
    char c;

    printf("int address : %u\n", &a);       // 주소 연산자 %u
    printf("double address : %u\n", &b);
    printf("char address : %u\n", &c);

    return 0;
    //  int address : 1540405340 -> 할때마다 달라짐
    //  double address : 1540405344
    //  char address : 1540405339
}

//교수님 IR 코드 _ 함수 추가로 가독성 좋게
#define MAX_N 16

void classify_by_threshold(const int value[], int label[], int n, int threshold);
int count_black(const int label[], int n);
double average_index_of_black(const int label[], int n);

int main(void)
{
    int N, threshold;
    int value[MAX_N];
    int label[MAX_N];

    printf("센서 개수 입력(1~%d): ", MAX_N);
    scanf("%d", &N);

    printf("센서 값 %d개 입력: ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &value[i]);
    }

    printf("임계값 입력: ");
    scanf("%d", &threshold);
    
    classify_by_threshold(value, label, N, threshold);
    int black_count = count_black(label, N);
    double center = average_index_of_black(label, N);

    printf("\nlabel = ");
    for (int i = 0; i < N; i++) {
        printf("%d  ", label[i]);
    }
    printf("\nblack_count = %d\n", black_count);
    if (black_count == 0) {
        printf("라인 없음 \n");
    } else {
        printf("index_avg = %.2lf\n", center);
    }

    return 0;
}

void classify_by_threshold(const int value[], int label[], int n, int threshold)
{
    for (int i = 0; i < n; i++) {
        if (value[i] < threshold){
            label[i] = 1;
        } else {
            label[i] = 0;
        }
    }
}

int count_black(const int label[], int n)
{
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += label[i];
    }
    return cnt;
}

double average_index_of_black(const int label[], int n)
{
    int sum = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        sum += i * label[i];
        cnt += label[i];
    }
    if (cnt == 0) return -1.0;
    return (double)sum / cnt;
}

// 나의 IR 코드 - 임계 값 기준으로 cnt
int main(void)
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
    printf("\nblack count = %d", &black_count);
    if (black_count <= 0) {
        printf("라인 없음");
    } else {
        printf("index_avg = %lf\n", &index_avg);
    }

}
*/