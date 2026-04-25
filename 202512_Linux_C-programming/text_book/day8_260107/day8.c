#include <stdio.h>
//15-3.c
void print_str(char **pps, int cnt);

int main(void)
{
    char *ptr_ary[] = {"eagle", "tiger", "lion", "squirrel"};   // 포인터의 주소를 보냄
    int count;

    count = sizeof(ptr_ary) / sizeof(ptr_ary[0]);
    print_str(ptr_ary, count);      // 포인터의 주소를 보냄

    return;
}

void print_str(char **pps, int cnt) // 그래서 여기서 ** 로 받음
{
    int i;

    for (i = 0; i < cnt; i++){
        printf("%s\n", pps[i]);
    }
}

/*
//15-2.c
// 100, 200, 300, 400 생각하면서 그림그리기 (ppa, ppb는 주소 500, 600)
void swap_ptr(char **ppa, char **ppb);

int main(void)
{
    char *pa = "success";
    char *pb = "failure";

    printf("pa -> %s, pb -> %s\n", pa, pb);
    swap_ptr(&pa, &pb);             // **를 받으니까 포인터(pa)의 & 달고 전달
    printf("pa -> %s, pb -> %s\n", pa, pb);

    return 0;
}

void swap_ptr(char **ppa, char **ppb)       // 여기서 별의 개수 및 의미 파악
{
    char *pt;

    pt = *ppa;
    *ppa = *ppb;
    *ppb = pt;
}


//15-1.c
int main(void)
{
    int a = 10;
    int *pi;
    int **ppi;

    pi = &a;
    ppi = &pi;

	printf("----------------------------------------------------\n");
	printf("변수	변숫값    	&연산	   *연산   	**연산\n");
	printf("----------------------------------------------------\n");
	printf("  a%12d%12u\n", a, &a);
	printf(" pi%12u%12u%12d\n", pi, &pi, *pi);
	printf("ppi%12u%12u%12u%12u\n", ppi, &ppi, *ppi, **ppi);
	printf("----------------------------------------------------\n");

    return 0;
}


//test 배열 값 계산
//5행6열 2차원 배열을 선언하고 4행 5열은 1~20 으로 초기화
//마지막 열에는 각행의 합, 마지막 행에는 각 열의 합 / 이후 전체 배열의 값
//이후 rows 랑 cols 에 값 넣는 식으로 -> 안됨 동적할당 받아야 되서 어려움
#define ROWS 5
#define COLS 6
#define DATA_ROWS (ROWS -1)
#define DATA_COLS (COLS -1)

int main(void)
{
    int ary[ROWS][COLS] = {0};
    int i, j;
    int cnt = 1;
    int r_total, c_total;

    for (i = 0; i < DATA_ROWS; i++) {
        r_total = 0;
        for (j = 0; j < DATA_COLS; j++) {
            ary[i][j] = cnt;
            r_total += ary[i][j];
            cnt++;
        }
        ary[i][DATA_COLS] = r_total;
    }

    for (j = 0; j < COLS; j++) {
        c_total = 0;
        for (i = 0; i < DATA_ROWS; i++) {
            c_total += ary[i][j];
        }
        ary[DATA_ROWS][j] = c_total;
    }
    printf("   가로세로의 합 구하기\n");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%4d", ary[i][j]);
        }
        printf("\n");
    }
    printf("전체 배열(%d)(%d)의 값: [%d]\n", DATA_ROWS, DATA_COLS, ary[DATA_ROWS][DATA_COLS]);
    return 0;

}


//14-7.c 포인터배열
int main(void)
{
    int ary1[4] = {1, 2, 3, 4};
    int ary2[4] = {11, 12, 13};         // 0 초기화 확인
    int ary3[4] = {21, 22, 23, 24};
    int *pary[3] = {ary1, ary2, ary3};      // 선언할 때는 1차원
    int i, j;
    int cnt = 0;
                        // pary[1] = ary1 : ary1[1] -> pary[1][1]
                        // pary[2][2] = *(pary[2] + 2) = *(300 + (2 * sizeof(int)))
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            cnt += pary[i][j];
            printf("%5d", pary[i][j]);      // 붙여쓰지만 하나는 아니다
        }
        printf("\n");
    }
    printf("종합: [%d]\n", cnt);

    return 0;
}

//14-6.c
int main(void)
{
    char *pary[5];
    int i;

    pary[0] = "dog";
    pary[1] = "elephant";
    pary[2] = "horse";
    pary[3] = "tiger";
    pary[4] = "lion";

    for (i = 0; i < 5; i++) {
        printf("%s\n", pary[i]);        // %s, str 만 쓰는거처럼 str 자체가 주소(& 없음)
    }

    return 0;
}

//14-5.c
int main(void)
{
    int score[2][3][4] = {
        { {72, 80, 95, 60}, {68, 98, 83, 90}, {75, 72, 84, 90}},
        { {66, 85, 90, 88}, {95, 92, 88, 95}, {43, 72, 56, 75}}
    };

    int i, j, k;        //  i는 iteration(반복), 이후는 아마 연속?? - gpt는 인덱스

    for (i = 0; i < 2; i++) {
        printf("%d반 점수...\n", i + 1);
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 4; k++) {
                printf("%5d", score[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}


//14-4.c 함수 초기화 할때 "123"로 넣으면 뒤에 널 / 하나하나('a' 'b') 하면 마지막 널 넣어주기
int main(void)
{
    char animal1[5][10] = {
        {'d','o','g','1','\0'},
        {'d','o','g','2','\0'},
        {'d','o','g','3','\0'},
        {'d','o','g','4','\0'},
        {'d','o','g','5','\0'}
    };

    char animal2[][10] = { "dog", "tiger", "rabbit", "horse", "cat"};
    int i;
    for (i = 0; i < 5; i++) {
        printf("%s\t", animal1[i]);
    }
    printf("\n");
    for (i = 0; i < 5; i++) {
        printf("%s\t", animal2[i]);
    }

    return 0;
}


//14-3.c
int main(void)
{
    char animal[5][20];
    int i;
    int count;

    printf("animal[0]의 사이즈 = %ld\n", sizeof(animal[0])); // 2차원에서 행만 쓰면 열 자동
    //printf("animal[][0]의 사이즈 = %d\n", sizeof(animal[][0])); // 2차원에서 행만 쓰면 열 자동
    //행은 생략불가 표현, 차라리 sizeof(animal[0]) / sizeof(animal[0][0]); 으로 구하기
    printf("animal[0][0]의 사이즈 = %ld\n", sizeof(animal[0][0])); // 2차원에서 행만 쓰면 열 자동
    count = sizeof(animal) / sizeof(animal[0]);     // 이게 젤 중요한 포인트 - 100 / 20
    for (i = 0; i < count; i++) {
        scanf("%s", animal[i]);
    }
    for (i = 0; i < count; i++) {
        printf("%s\t", animal[i]);
    }
    printf("\n");

    return 0;
}


//14-2.c
int main(void)
{
    int num[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%5d", num[i][j]);
        }
        printf("\n");
    }

    return 0;
}


//14-1.c
int main(void)
{
    int score[3][4];
    int total;
    double avg;
    int i, j;

    for (i = 0; i < 3; i++) {
        printf("4과목의 점수 입력: ");
        for (j = 0; j < 4; j++){
            scanf("%d", &score[i][j]);
        }
    }

    for (i = 0; i < 3; i++) {
        total = 0;
        for (j = 0; j < 4; j++) {
            total += score[i][j];
        }
        avg = total / 4.0;
        printf("총점: %d, 평균: %.2lf\n", total, avg);
    }

    return 0;
}


//13-8.c - 다음에 시간 되면 하나 받고 자체적으로 곱하는거 해서 쓸 수 있는지 확인 (검증 제대로)
//정적 지역 변수나 전역 변수와 같이 함수가 반환된 후에도 저장 공간이 유지되는 경우만 주소를 반환
int *sum(int a, int b);
int *mul(int a);

int main(void)
{
    int *resp;
    int *multi;
    resp = sum(10,20);
    printf("두 정수의 합: %d\n", *resp);

    multi = mul(10);
    printf("정수값 확인: %d\n", *multi);
    multi = mul(10);
    printf("정수값 확인: %d\n", *multi);
    multi = mul(10);
    printf("정수값 확인: %d\n", *multi);
    return 0;
}
int *sum(int a, int b)
{
    static int res;

    res = a + b;

    return &res;        // 주소를 주는게 핵심 (구 컴파일러에서 int* 로 표시되는 이유)
}
int *mul(int a)
{
    static int result;

    result = (a * 2) + 1;

    return &result;
}


//13-7.c
void add_ten(int *pa);

int main(void)
{
    int a = 10;

    add_ten(&a);
    printf("a = %d\n", a);

    return 0;
}

void add_ten(int *pa)
{
    *pa += 10;
}


// 13-6.c
void add_ten(int a);     // void를 int로 바꿔도 동일

int main(void)
{
    int a = 10;

    add_ten(a);
    printf("a: %d\n", a);

    return 0;
}

void add_ten(int a)     // main에 있는 a를 복사해서 이 함수에 a를 만듬
{
    a += 10;
}

//13-5.c 컴파일러가 알아서 레지스터 넣어줌 (양이 많으면) - 10만이나 100만이나 비슷
//register = 0.059 seconds
//int i = 0.06 seconds 
int main(void)
{
    register int i;
    auto int sum = 0;

    for (i = 1; i < 1000000; i++) {
        sum += i;
    }

    printf("%d\n", sum);

    return 0;
}

//교수님 실험 문제 - 3 / 4 / 5 / 3 / 7
// static 정적 변수의 초기화는 프로그램 시작 시 단 한 번
void fA(void)
{
    static int x = 1;
    x += 2;
    printf("A = %d\n", x);
}
void fB(void)
{
    static int x = 5;
    x -= 1;
    printf("B = %d\n", x);
}

int main(void)
{
    fA();
    fB();
    fA();
    fB();
    fA();

    return 0;
}

//13-4.c
void auto_func(void);
void static_func(void);

//int a;    이렇게 선언해도 동일
int main(void)
{
    int i;
    //static int a;     //이렇게 선언하면 static_func으로 안 날라감

    printf("일반 지역 변수(auto)를 사용한 함수...\n");
    for (i = 0; i < 3; i++) {
        auto_func();
    }

    printf("정적 지역 변수(static)를 사용한 함수...\n");
    for (i = 0; i < 3; i++) {
        static_func();
    }

    return 0;
}

void auto_func(void)
{
    auto int a = 0;
    a++;
    printf("%d\n", a);
}

void static_func(void)
{
    static int a;           // 정적 변수라 0으로 초기화
    a++;
    printf("%d\n", a);
}


//13-3.c
void assign10(void);
void assign20(void);

int a;          // 전역으로 지정, 전역 변수는 알아서 0으로 초기화 해줌

int main(void)
{
    printf("Before 'A': %d\n", a);

    assign10();
    assign20();

    printf("After 'A': %d\n", a);
    
    return 0;
}

void assign10(void)
{
    a = 10;
}

void assign20(void)
{
    int a;   // 이렇게 선언하면 이거 우선 사용

    a = 20;
}


//13-2.c
int main(void)
{
    int a = 10, b = 20;

    printf("교환 전 a & b : %d, %d\n", a, b);
    {
        int temp;
        //int a, b;           // 같은 이름의 변수가 둘 이상이면 가까운 변수 사용

        temp = a;
        a = b;
        b = temp;
    }                           // 이 괄호닫음으로 temp는 사라짐
    printf("교환 후 a & b : %d, %d\n", a, b);

    return 0;
}


//13-1.c 매개변수 void 에서 a로 변경해도 동일
void assign(int a);
int main(void)
{
    auto int a = 0; // 자동 지정인데 안 씀

    assign(a);
    printf("main함수 a: %d\n", a);

    return 0;
}

void assign(int a)
{
    //int a;

    a = 10;
    printf("assign함수 a: %d\n", a);
}


//strcpy, strcat, strlen, strcmp 직접 구현 - 첫 fgets만 추가 검증
void m_strcpy(char *p1, char *p2);
void m_strcat(char *p1, char *p2);
int m_strlen(char *p);
int m_strcmp(char *p1, char *p2);   // 원래는 차이값이 나온다
#define MAX_SIZE 5

int main(void)
{
    char p1[MAX_SIZE];
    char p2[MAX_SIZE];
    int select, r;
    printf("입력 가능한 최대 사이즈 [%d]\n", MAX_SIZE-1);
    printf("p1에 문자 입력: ");
    fgets(p1, sizeof(p1), stdin);
    if (p1[m_strlen(p1) -1] == '\n') {
        p1[m_strlen(p1) -1] = '\0';
    } else if (m_strlen(p1) == MAX_SIZE-1) {
        while ((r = getchar()) != '\n' && r != EOF) {}
    } else {
        printf("fgets_p1 에러");
        return 0;
    }
    
    printf("p2에 문자 입력: ");
    fgets(p2, sizeof(p2), stdin);
    if (p2[m_strlen(p2) -1] == '\n') {
        p2[m_strlen(p2) -1] = '\0';
    } else if (m_strlen(p2) == MAX_SIZE-1) {
        while ((r = getchar()) != '\n' && r != EOF) {}
    } else {
        printf("fgets_p2 에러");
        return 0;
    }
    printf("함수를 선택하세요.\n1. strcpy\t2. strcat\t3. strlen\t4. strcmp\t5. Exit\n");
    scanf("%d", &select);
    
    switch (select) {
        case 1:
            m_strcpy(p1, p2);
            printf("p1: %s\np2: %s", p1, p2);
            break;
        case 2:
            m_strcat(p1, p2);
            printf("p1: %s\np2: %s", p1, p2);
            break;
        case 3:
            printf("어느 배열을 계산할까요? (1 혹은 2)");
            scanf("%d", &r);
            if (r == 1) {
                printf("p1의 길이는: %d", m_strlen(p1));
            } else if ( r == 2) {
                printf("p2의 길이는: %d", m_strlen(p2));
            } else {
                printf("선택 번호 오류");
            }
            break;
        case 4:
            printf("설명: 1이면 p1이 나중, -1이면 p2가 나중\n");
            r = m_strcmp(p1, p2);
            if (r != 0) {
                printf("strcmp 결과값: %d", r);
            }
            break;
        case 5:
            printf("Exit 선택하여 종료");
            break;
        default:
            printf("번호 오류");
            break; 
    }
    printf("\n");
    return 0;

}

void m_strcpy(char *p1, char *p2)
{
    int i = 0, j = 0;

    while ((p2[j] != '\0') && (i < MAX_SIZE -1)) {
        p1[i] = p2[j];
        i++;
        j++;
    }
    p1[i] = '\0';

    return;
}

void m_strcat(char *p1, char *p2)
{
    int i = 0, j = 0;

    while ((p1[i] != '\0') && (i < MAX_SIZE -1)) {
        i++;
    }

    while ((p2[j] != '\0') && (i < MAX_SIZE -1)) {
        p1[i] = p2[j];
        i++;
        j++;
    }
    p1[i] = '\0';

    return;
}

int m_strlen(char *p)
{
    int len = 0;
    while (*p != '\0') {
        len++;
        p++;
    }

    return len;
}

int m_strcmp(char *p1, char *p2)
{
    int i = 0, j = 0;
    
    while ((p1[i] != '\0') && (p2[j] != '\0')) {
        if (p1[i] > p2[j]) {
            return 1;
        } else if (p1[i] < p2[j]) {
            return -1;
        } else {
            i++;
            j++;
        }
    }
    
    if (p1[i] == '\0' && p2[j] == '\0') {
        printf("두 문자열은 동일합니다.");
        return 0;
    } else if (p1[i] == '\0'){
        printf("선행 문자 길이(%d)까지는 동일", i);
        return 0;
    } else {
        printf("후행 문자 길이(%d)까지는 동일", j);
        return 0;
    }
}

/// 너무 길어서 구분용

//12-12.c
#include <string.h>

int main(void)
{
    char str1[80] = "pear";
    char str2[80] = "peach";

    printf("사전에 나중에 나오는 과일 이름: ");     // 아스키코드 그대로 앞 번호라 대문자가 앞
    if (strcmp(str1, str2) > 0)     // 나중에 나오면 1, 아니면 -1, 같으면 0
        printf("%s\n", str1);       // str1이 str2보다 먼저 나오면 -1 = 순서 주의
    else                            // 즉 아스키 코드가 뒤에 있으면 1
        printf("%s\n", str2);

    return 0;
}

//12-11.c + strlen를 표현할 함수 만들기
#include <string.h>

int length(char *p);
int main(void)
{
    char str1[80], str2[80];
    char *resp;

    printf("2개의 과일 이름 입력: ");
    scanf("%s%s", str1, str2);
    if (strlen(str1) > strlen(str2))
        resp = str1;
    else
        resp = str2;
    printf("이름이 긴 과일은: %s\n", resp);
    printf("str1 & str2의 길이 strlen 함수: %d, %d\n", strlen(str1), strlen(str2));
    printf("내 함수로 구현한 길이: %d, %d\n", length(str1), length(str2));

    return 0;
}

int length(char *p)
{
    int i = 0;

    while (1) {
        if (p[i] != '\0')
            i++;
        else
            break;
    }

    return i;
}

//12-10.c
#include <string.h>

int main(void)
{
    char str[80] = "straw";
    printf("후단까지 체크해보기: %d\n", str[6]);
    strcat(str, "berry");       // 널부터 데이터 붙임
    printf("%s\n", str);
    strncat(str, "piece", 3);
    printf("%s\n", str);

    return 0;
}

//12-9.c
#include <string.h>
int main(void)
{
    char str[20] = "mango tree";

    strncpy(str, "apple-pie", 5);       // n 개 만큼

    printf("%s\n", str);

    return 0;
}


//12-8.c
#include <string.h>

int main(void)
{
    char str1[80] = "strawberry";
    char str2[80] = "apple";
    char *ps1 = "banana";       // 변수 안에 넣는게 아닌 어딘가에 banana를 찾아 포인터
    char *ps2 = str2;

    printf("최초 문자열: %s\n", str1);

    strcpy(str1, str2);     // apple \0 erry \0
    printf("str2로 바꾼 문자열: %s\n", str1);
    printf("후단까지 체크해보기: %c\n", str1[9]);

    strcpy(str1, ps1);
    printf("ps1으로 바꾼 문자열: %s\n", str1);
    printf("후단까지 체크해보기: %c\n", str1[9]);

    strcpy(str1, ps2);
    printf("ps2로 바꾼 문자열: %s\n", str1);

    strcpy(str1, "banana");
    printf("문자 직접 바꾼 문자열: %s\n", str1);
    
    return 0;   
    
}
*/