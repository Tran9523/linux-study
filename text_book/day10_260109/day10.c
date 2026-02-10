#include <stdio.h>

// 차동구동 로봇 속도 계산
// 메인에서 왼쪽/오른쪽 바퀴 속도 바퀴 반지름 바퀴 간 기름
typedef struct {        //좌우 바퀴 속도
    double left;
    double right;
} WheelSpeed;

typedef struct {        //선 속도(앞으로 가는 속도) & 각 속도(돌아가는 속도)
    double linear;  
    double angular;
} RobotSpeed;

RobotSpeed computeSpeed(WheelSpeed w, double w_rad, double w_dist);

int main(void)
{
    WheelSpeed w = {0.0, 0.0};
    RobotSpeed r = {0.0, 0.0};
    double w_rad, w_dist;

    printf("좌우측 바퀴의 속도[rad/s]: ");
    scanf("%lf%lf", &w.left, &w.right);

    printf("바퀴 반지름[m]: ");
    scanf("%lf", &w_rad);
    printf("바퀴 간 거리[m]: ");
    scanf("%lf", &w_dist);

    r = computeSpeed(w, w_rad, w_dist);

    printf("선속도: %.2lf m/s\n", r.linear);
    printf("각속도: %.2lf rad/s\n", r.angular);

    return 0;
}

RobotSpeed computeSpeed(WheelSpeed w, double w_rad, double w_dist)
{
    RobotSpeed r;

    r.linear  = w_rad * (w.left + w.right) / 2.0;
    r.angular = w_rad * (w.right - w.left) / w_dist;

    return r;
}


/*
//로봇 이동 계산 하기
typedef struct {
    int x;
    int y;
} Position;

void move(Position *p, int dx, int dy);
int move_value(int *a, int *b);

int main(void)
{
    int a, b;
    Position robot = {0, 0};

    printf("1회 이동\n");
    if (move_value(&a, &b)) move(&robot, a, b);

    printf("2회 이동\n");
    if (move_value(&a, &b)) move(&robot, a, b);
    
    printf("로봇 최종 위치: [%d / %d]\n", robot.x, robot.y);

    return 0;
}

void move(Position *p, int dx, int dy)
{
    p->x += dx;
    p->y += dy;
}

int move_value(int *a, int *b)
{
    printf("위치 이동할 값을 입력하세요[x, y]: ");
    if (scanf("%d%d", a, b) != 2) {
        printf("입력 오류\n");
        return 0;
    }
    return 1;

}
/*
//성적처리 시스템 (5명의 학번, 이름, 국어, 영어, 수학) -> 총점 / 평균 / 등급
#define NUMBER 5

typedef struct {
    int num;    char grade;
    int kor;    int eng;
    int math;   int total;
    double avg;
    char name[16];
} stu;

void scanf_array(stu list[], int n);
void sort_array(stu list[], int n);
void clear_stdin(void);
void print_array(stu list[], int n);

int main(void)
{
    stu list[NUMBER];      //선언 하는 방식에 대해서 항상 생각하기

    scanf_array(list, NUMBER);

    printf("정렬 전 데이터\n");
    print_array(list, NUMBER);
    

    sort_array(list, NUMBER);

    printf("정렬 후 데이터\n");
    print_array(list, NUMBER);

    return 0;
}

void scanf_array(stu list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("학번: ");
        if (scanf("%d", &list[i].num) != 1) {
            printf("학번은 숫자만 입력하세요.\n");
            clear_stdin();
            i--;        // i 줄이는게 핵심
            continue;
        }
        clear_stdin();
        printf("이름: ");
        scanf("%15s", list[i].name);
        clear_stdin();
        printf("국어, 영어, 수학 점수: ");
        if (scanf("%d %d %d", &list[i].kor, &list[i].eng, &list[i].math) != 3) {
            printf("점수는 숫자 3개로 입력하세요.\n");
            clear_stdin();
            i--;
            continue;
        }
        clear_stdin();
        list[i].total =  list[i].kor + list[i].eng + list[i].math;
        list[i].avg = list[i].total / 3.0;
        if ((list[i].avg) >= 90) {
            list[i].grade = 'A';
        } else if ((list[i].avg) >= 80) {
            list[i].grade = 'B';
        } else if ((list[i].avg) >= 70) {
            list[i].grade = 'C';
        } else {
            list[i].grade = 'F';
        }
        clear_stdin();
        printf("[%d]명 입력 완료 - 전체 %d명\n", i+1, n);
    }
}

void sort_array(stu list[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n -1 - i; j++) {
            if (list[j].avg < list[j + 1].avg) {
                stu tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
}

void print_array(stu list[], int n)
{
    printf("학번/이름:\t국어/영어/수학     총점 / 평균 / 학점\n");
    for (int i = 0; i < n; i++) {
        printf("%d/%s:\t%3d /%3d /%3d     %4d / %4.1lf / %c",
            list[i].num, list[i].name, list[i].kor, list[i].eng, list[i].math,
            list[i].total, list[i].avg, list[i].grade);
        printf("\n");
    }
}

void clear_stdin(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

/*
//17-12.c   typedef = 다시 재정의하기(편해서 자주 씀) 보통 하단 형태로 많이 씀
typedef struct {
    int num;
    double grade;
} Student;      // 대문자인거는 그냥 설정한거지 소문자로 계속 써도 됨
//struct student {
//    int num;
//    double grade;
//};
//typedef struct student Student; // 기존에는 struct student s1 이렇게 작성 => Student
void print_data(Student *ps);

int main(void)
{
    Student s1 = {315, 4.2};

    print_data(&s1);

    return 0;
}
void print_data(Student *ps)
{
    printf("Num: %d\n", ps->num);
    printf("Grade: %.1lf\n", ps->grade);
}

/*
//17-11.c 열거형(enum) = 코드를 눈으로 읽기 편하게
//뭔지 한번 더 물어보기 ( 0, 1, 2, 3 의 의미라고 함) = 의미를 코드에 남기기 위해
enum season {SPRING, SUMMER, FALL, WINTER};

int main(void)
{
    enum season ss;
    char *pc = NULL;

    ss = SPRING;
    
    switch (ss) {
        case SPRING:
            pc = "inline"; break;
        case SUMMER:
            pc = "swimming"; break;
        case FALL:
            pc = "trip"; break;
        case WINTER:
            pc = "skiing"; break;
    }
    printf("나의 레저 활동 => %s\n", pc);
}


/*
//17-10.c - 공용체(union) = 큰거 기준으로 하나만 전달
//전체 8바이트를 4 & 8이 나눠서 사용 [구조체 였다면 16바이트]
union student {
    int num;
    double grade;
};

int main(void)
{
    union student s1 = {315};

    printf("학번: %d\n", s1.num);
    s1.grade = 4.4;
    printf("학점: %.1lf\n", s1.grade);
    printf("학번: %d\n", s1.num);
    
    return 0;
}


/*
//17-9.c - current는 처음 선언할때 값이 없었음(정확히는 head로 쭉 대체해도 동일)
//GPT: 포인터 변수는 주소 하나만 가진다!!
struct list{
    int num;
    struct list *next;      // 형태가 같은 자기 참조형
};

int main(void)
{
    struct list a = {10, 0}, b = {20, 0}, c = {30, 0};  // a = (10, 0_ptr)
    struct list *head = &a, *current;   // *** 매우 중요, head는 &a 인거고 current랑 무관
                            // 구조체 a를 가리키는 포인터 head인거고 자체가 구조체는 아님
    a.next = &b;    // a= 10, 200번지
    b.next = &c;

    printf("head->num : %d\n", head->num);
    printf("head->next->num : %d\n", head->next->num);

    printf("list all: ");
    current = head;     // current는 여기와서 드디어 값이 배정됨(위에까지는 공백)
    while (current != NULL) {
        printf("%d   ", current->num);  // current는 백번지 -> 거기의 next는 200번지
        current = current->next;        // 첫 꼬리(&a)가 나오고 &b -> &c 0 이후엔 NULL
    }
    printf("\n");

    return 0;
}

/*
//17-8.c    구조체 배열 처리
struct address {
    char name[20];
    int age;
    char tel[20];
    char addr[80];
};
void print_list(struct address *lp);

int main(void)
{
    struct address list[5] = {
        {"홍길동", 23, "111-1111", "울릉도 독도"},
        {"이순신", 35, "222-2222", "서울 건천동"},
        {"장보고", 19, "333-3333", "완도 청해진"},
        {"유관순", 15, "444-4444", "충남 천안"},
        {"안중근", 45, "555-5555", "황해도 해주"},
    };

    print_lsit(list);       //배열명 = 주소
}

void print_list(struct address *lp) // lp주소로 받았기에 출력 형태가 a->a 형태
{
     for (int i = 0; i < 5; i++) {
        printf("%10s%5d%15s%20s\n", (lp+i)->name, (lp+i)->age, (lp+i)->tel, (lp+i)->addr);
    }
}

/*
//17-7.c
struct address {
    char name[20];
    int age;
    char tel[20];
    char addr[80];
};

int main(void)
{
    struct address list[5] = {
        {"홍길동", 23, "111-1111", "울릉도 독도"},
        {"이순신", 35, "222-2222", "서울 건천동"},
        {"장보고", 19, "333-3333", "완도 청해진"},
        {"유관순", 15, "444-4444", "충남 천안"},
        {"안중근", 45, "555-5555", "황해도 해주"},
    };

    for (int i = 0; i < 5; i++) {
        printf("%10s%5d%15s%20s\n", list[i].name, list[i].age, list[i].tel, list[i].addr);
    }       //반복문을 통해 접근이 가능하다의 의의

    return 0;
}

/*
//17-6.c 출력 형태 주목 [ (*ps). == ps-> == yuni. ]
struct score {
    int kor;
    int eng;
    int math;
};

int main(void)
{
    struct score yuni = {90, 80, 70};
    struct score *ps = &yuni;   //가리키는 형태가 구조체인거지 pi가 구조체는 아님

    printf("kor: %d\n", (*ps).kor);
    printf("eng: %d\n", ps->eng);       //이 형태가 보편
    printf("math: %d\n", ps -> math);
}

/*
//17-5.c
struct vision {
    double left;
    double right;
};

struct vision exchange (struct vision robot);   // exchange라는 함수를 만든거임
            //반환형이 구조체일뿐
void exch_point(struct vision *robot);  // 값을 안 바꾸고 주소로 접근하니 void 반환형

int main(void)
{
    struct vision robot;
    printf("시력 입력: ");
    scanf("%lf%lf", &(robot.left), &(robot.right)); 
    exch_point(&robot);
    //robot = exchange(robot);
    printf("바뀐 시력: %.1lf  %.1lf\n", robot.left, robot.right);

    return 0;
}

struct vision exchange(struct vision robot)
{
    double temp;

    temp = robot.left;
    robot.left = robot.right;
    robot.right = temp;

    return robot;           // 보내는 형태가 구조체임을 확인
}

void exch_point(struct vision *robot)
{
    double temp;

    temp = robot->left;     //robot->left = (*robot).left
    robot->left = robot->right;
    robot->right = temp;

}
/*
//17-4.c
struct student {
    int id;
    char name[20];
    double grade;
};

int main(void)
{                       // 시작과 동시에 초기화 가능
    struct student s1 = {315, "홍길동", 2.4 },
                   s2 = {316, "이순신", 3.7 },
                   s3 = {317, "세종대왕", 4.4};
    struct student max;

    max = s1;
    if (s2.grade > max.grade) max = s2;
    if (s3.grade > max.grade) max = s3; //구조체 넣을때는 주소나 포인터 없이(특정 상황이면 필요)

    printf("ID: %d\n", max.id);
    printf("Name: %s\n", max.name);
    printf("Grade: %.1lf\n", max.grade);

    return 0;
}

/*
//17-3.c
struct profile {
    int age;
    double height;
};

struct student {
    struct profile pf;
    int id;
    double grade;
};

int main(void)
{
    struct student yuni;

    yuni.pf.age = 17;
    yuni.pf.height = 164.5;
    yuni.id = 315;
    yuni.grade = 4.3;

    printf("나이: %d\n", yuni.pf.age);
    printf("키: %.1lf\n", yuni.pf.height);
    printf("학번: %d\n", yuni.id);
    printf("학점: %.1lf\n", yuni.grade);

    return 0;
}

/*
//17-2.c
#include <stdlib.h>
#include <string.h>

#define SIZE 81
struct profile{
    char name[20];
    int age;
    double height;
    char *intro;
};

int main(void)
{
    struct profile yuni;

    strcpy(yuni.name, "서하윤");
    yuni.age = 17;
    yuni.height = 164.5;

    //yuni.intro = (char *)malloc(80));
    yuni.intro = (char *)calloc(SIZE, sizeof(char));
    if (yuni.intro == NULL) {
        printf("# 메모리가 부족합니다.");
        exit(1);
    }
    printf("자기소개 [최대: %d자]: ", SIZE-1);
    fgets(yuni.intro, SIZE, stdin);
    //gets(yuni.intro); 오류가 나기 너무 쉬운 함수인 gets

    printf("이름:\t%s\n", yuni.name);
    printf("나이:\t%d\n", yuni.age);
    printf("키:\t%.1lf\n", yuni.height);
    printf("자기소개: %s\n", yuni.intro);
    free(yuni.intro);

    return 0;
}

/*
//test1 패딩바이트 크기 줄여보기
//어디에 진짜 비었는지 주소값으로 확인이 가능함(나중에 시간된다면 꼭 확인)
struct student1 {
    char ch1;
    short num;
    char ch2;
    int score;
    double grade;
    char ch3;
};

struct student2 {
    char ch1;
    short num;
    char ch2;
    char ch3;
    int score;
    double grade;
};

struct student3 {
    char ch1;
    short num;
    char ch2;
    int score;
    double grade;
    char ch3;
    int score2
};

int main(void)
{
    struct student1 s1;
    struct student2 s2;
    struct student3 s3;

    printf("s1의 사이즈: %ld\n", sizeof(s1));
    printf("s2의 사이즈: %ld\n", sizeof(s2));
    printf("s3의 사이즈: %ld\n", sizeof(s3));

    return 0;
}
//  s1의 사이즈: 32
//  s2의 사이즈: 24
//  s3의 사이즈: 32

/*
//17-1.c 구조체는 포인터 만큼이나 많이 씀 (현업에서는 포인터랑 배열만 잘 써도 뽑겟다 마인드)
//구조체 배울때 붕어빵 틀 이라고도 표현 (대신 이건 제일 긴 기준으로 배정 + 패딩바이트 생각)
struct student {
    int num;
    double grade;
};          // 구조체 예약은 밖에서 선언

int main(void)
{
    struct student s1;      // 얘는 붕어빵

    s1.num = 2;             // . 접근 연산자
    s1.grade = 2.7;
    printf("학번: %d\n", s1.num);
    printf("학점: %.1lf\n", s1.grade);

    return 0;
}
*/