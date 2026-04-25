#include <stdio.h>
// + scanf / gets / fgets - 개항 포함?
// + puts / fputs - 개행문과 처리 하는 방법 리뷰
// 다음 프로그램의 문제를 찾고 코드 추가 삭제 바르게 실행
#include <string.h>

int main(void)
{
    char ani[20];
    char why[80];
    printf("좋아하는 동물 : ");
    //fgets(ani, sizeof(ani), stdin);       // 2. 예시에서 이거 수정
    //ani[strlen(ani) -1] = '\0';           // 2. 개행문자 처리하고 혹은 아래 fgets 수정
    scanf("%s", ani);
    printf("좋아하는 이유 : ");
    //getchar();      //  1. 예시에서 추가하면 끝
    //fgets(why, sizeof(why), stdin);
    //scanf("%s", why);         // 이건 공백을 받을 수 없어서 "%[^\n]" 식으로 바꿔야
    printf("%s is %s", ani, why);
    //printf("print: %d", why[0]); - 개행 문자 포함이라 예시 그대로 가면 10 나옴

    return 0;
}
// 결과 예시
// 좋아하는 동물 : dog
// 좋아하는 이유 : very faithhul
// dog is very faithful

/*
//test pa = "mango" 하고 3번째 문자를 m으로 바꾸기? -> 문자열 상수라 변경 불가
int main(void)
{
    char *pc = "mango";

    printf("%c\n", pc[2]);
    pc[2] = 'm';
    printf("%c\n", pc[2]);      // Segmentation fault (core dumped)
    
    return 0;
}


//12-7.c
int main(void)
{
    char str[80] = "apple juice";
    char *ps = "banana";

    puts(str);              // 출력 후 줄바꿈
    fputs(ps, stdout);
    puts("milk");

    return 0;
}


//12-6.c
int main(void)
{
    int age;
    char name[20];
    
    printf("나이 입력: ");
    scanf("%d", &age);
    gets();           //마찬가지로 버퍼로 못 받으니까 버리기
    //  getchar(); & scanf("%*c"); & fgetc(stdin); 등 사용가능
    printf("이름 입력: ");
    gets(name);
    printf("나이: %d, 이름: %s\n", age, name);

    return 0;
}


//12-5.c
#include <string.h>

int main(void)
{
    char str[80];       // 이게 10이라면 마지막 위치는 널문자가 들어가서 변환 필요 없 

    printf("공백이 포함된 문자열 입력: ");
    fgets(str, sizeof(str), stdin);     // sizeof 넣는걸 생활화 [엔터까지 저장됨]
    printf("전체 문자열 넓이: %ld\n", strlen(str));
    str[strlen(str) -1] = '\0';     // 보충한 내용 &&& strlen = 문자열의 길이
    printf("입력된 문자열은 %s입니다.\n", str);
    printf("이후 문자열 넓이: %ld\n", strlen(str));
    // 버퍼에 \n \0 이 연달아 있어서 자동 엔터 = 즉 개행 엔터까지

    return 0;
}


//12-4.c
int main(void)
{
    char str[80];

    printf("공백이 포함된 문자열 입력: ");
    gets(str);      // gets는 항상 오버플로우 조심
    printf("입력한 문자열: %s\n", str);    // 버퍼에서는 \n으로 끝 표시를 하지만
                                        // 배열에서는 \0을 붙임 - NUL 아스키코드0
    printf("첫 자리 확인: %c & %d\n", str[0], str[0]);
    return 0;
}

//12-3.c
int main(void)
{
    char str[80];

    printf("문자열 입력: ");
    scanf("%s", str);       // apple jam 교재 추천
    printf("첫 번째 단어: %s\n", str);
    scanf("%s", str);       // 추가 입력 없이 남는걸로 들어감(공백 없어야 2번)
    printf("버퍼에 남아 있는 두 번째 단어: %s\n", str);

    return 0;
}


//12-2.c - scanf("%s", a) 문자열 받을땐 &가 안 들어감!!
//100개 포인터를 선언해도 같은 주소를 바라봄(현재 값은 banana 들어가서 그렇지 동일)
int main(void)
{
    char *dessert = "apple";    // apple 이 저장된 주소값을
    char *dessert_2nd = "apple";
    char *dessert_3rd = "apple";

    printf("오늘 후식은 %s입니다.\n", dessert); // %s 는 주소를 주면 알아서 널 만날때까지 읽음
    dessert = "banana";
    printf("내일 후식은 %s입니다.\n", dessert); // u나 p로 주소값도 확인 가능

    while (*dessert != '\0'){
        putchar(*dessert);
        dessert++;  // 표현 주의 (dessert + 1) [ * & ]없음
    }                               // 실제로도 같게 출력됨
    printf("\n");
    printf("내일 후식은 %p입니다.\n", dessert);
    printf("내일 후식은 %p입니다.\n", dessert_2nd);
    printf("내일 후식은 %p입니다.\n", dessert_3rd);

    return 0;
}


//12-1.c 문자열 상수가 주소란 증거 [문자 'a' - 'A' = 32]
int main(void)
{
    printf("apple이 저장된 시작 주소 값: %p\n", "apple");   // %p 16진수로 주소
    printf("두 번째 문자의 주소 값: %p\n", "apple" + 1);
    printf("첫 번째 문자: %c\n", *"apple");
    printf("두 번째 문자: %c\n", *("apple" + 1));
    printf("배열로 표현한 세 번째 문자: %c\n", "apple"[2]);

    return 0;
}


//11-7.c / fgets_string & fgetc_char 임
// fgets(str, sizeof(str), stdin) 형태 기억
int main(void)
{
    int num, grade;
    printf("학번 입력: ");
    scanf("%d", &num);
    //getchar();          // 버퍼를 받아서 빼냄 = 버려버림 / 없으면 엔터치고 학점 없이 끝
    printf("학점 입력: ");
    //grade = getchar();      // 혹은 얘를 scanf로 받으면 없이 가능
    scanf(" %c", &grade);       // 그래서 앞에 공백 주면 넘기고 가능
    printf("학번: %d, 학점: %c", num, grade);   // 버퍼 남아있으면 아래 엔터까지 합쳐서 2번
    printf("\n");

    return 0;

}

// NULL까지 보고 싶음 -> 컴파일러가 알아서 끊어주는 느낌
int main(void)
{
    char str[9] = "Be happy!";

    printf("%s", str);

    return 0;
}

//11-6.c
void my_gets(char *str, int size);

int main(void)
{
    char str[7];

    my_gets(str, sizeof(str));
    printf("입력한 문자열 %s\n", str);

    return 0;
}

void my_gets(char *str, int size)
{
    int ch;
    int i = 0;

    ch = getchar();     // 바로 엔터치면 프로그램 종료
    while ((ch != '\n') && (i < size -1))
    {
        str[i] = ch;
        i++;
        ch = getchar();
    }
    str[i] = '\0';          // NULL을 넣어야 안전하게 됨 + 끝을 알려줌
}

//11-5.c
int main(void)
{
    int res;
    char ch;
    
    while (1) {     // 무한반복문
        res = scanf("%c", &ch);
        if (res == -1) break;
        printf("%d ", ch);
    }
}

//11-4.c
int main(void)
{
    char ch;
    int i;
                    
    for (i = 0; i < 5; i++) {
        scanf("%c", &ch);       // 버퍼에 대기하고 있는 얘를 바로 데려옴(그래서 입력 1번만)
        printf("%c", ch);
    }
    for (i = 0; i < 3; i++) {   // 하나 더 해서 4,5 테스트 - 678 출력되고 뒤에서는 8 중복
        scanf("%c", &ch);
        printf("%c", ch);
    }
    printf("%c", ch);       // 이러면 5번째 나왔던 문자가 중복해서 출력됨 for 하나 더 쓰면 8
    printf("\n");
    return 0;
}
//  i < 7 했을때 tiger
//              tiger
//              234
//              2

//11-3.c
int main(void)
{
    int ch;

    ch = getchar();     // char만 받는걸로 정해져있어서 붙여써도 하나만 받음
    printf("입력한 문자: ");
    putchar(ch);        // 이건 출력하는거
    putchar('\n');      // get은 받는 위치가 앞으로, put은 뒤로 받음

    return 0;
}

//11-2.c
int main(void)
{
    char ch1, ch2;

    scanf(" %c %c", &ch1, &ch2);       // scanf 공백 넣고 테스트
    //scanf("%c%c", &ch1, &ch2);
    // 2개 문자 연속 입력
    printf("[%c%c]\n", ch1, ch2);
    printf("%d & %d\n", ch1, ch2);      // 아스키 코드 확인

    return 0;
}

// 11-1.c
int main(void)
{
    char small, cap = 'G';

    if ((cap >= 'A') && (cap <= 'Z'))
    {
        small = cap + ('a' - 'A');
    }
    printf("대문지: %c %c", cap, '\n');     // 연습용이라 엔터를 %c로 받음
    printf("소문자: %c", small);

    return 0;
}

//test 문제
//각 달의 인수를 저장한 배열, Month[0]은 1월, Month 값을 한줄에 5개씩 출력
void print_month(int *mp);
void print_day(int *mp);

int main(void)
{
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    print_month(month);
    print_day(month);

    return 0;
}

void print_month(int *mp)
{
    int i, cnt = 0;

    for (i = 0; i < 12; i++) {              //각 달의 일수 출력
        if ((cnt % 5) == 0) printf("\n");      // 출력 개수가 5의 배수라면 줄 바꿈
        printf("%5d", mp[i]);
        cnt++;
    }
    printf("\n");
}

void print_day(int *mp)         //연습용 - gpt 도움받기
{
    int month, i;

    printf("\n출력할 달을 입력하세요 (1~12): ");
    scanf("%d", &month);

    if (month < 1 || month > 12) {
        printf("잘못된 달 입력입니다.\n");
        return;
    }

    printf("[%d월]\n", month);

    for (i = 1; i <= mp[month - 1]; i++) {
        printf("%2d ", i);

        if (i % 7 == 0)   // 7개 단위 줄바꿈
            printf("\n");
    }
    printf("\n");
}


//10-7.c
void input_ary(double *pa, int size);
double find_max(double *pa, int size);

int main(void)
{
    double ary[5];
    double max;
    int size = sizeof(ary) / sizeof(ary[0]);

    input_ary(ary, size);
    max = find_max(ary, size);
    printf("배열의 최댓값: %.1lf\n", max);

    return 0;
}

void input_ary(double *pa, int size)
{
    int i;

    printf("%d개의 실수값 입력: ", size);
    for (i = 0; i < size; i++) {
        scanf("%lf", pa + i);
    }   
}

double find_max(double *pa, int size)
{
    double max;
    int i, cnt = 0;

    max = pa[0];
    for (i = 1; i < size; i++) {
        if (pa[i] > max) {
            max = pa[i];
            cnt++;
        }
    }
    printf("%d번 바뀜\n", cnt);
    return max;
}

//10-6.c cf. 복습할때 숫자말고 문자열로도 해보기 + print_ary에서 size 해보기
#define ARY_LEN(x) (sizeof(x) / sizeof((x)[0]))
void print_ary(int *pa, int size);

int main(void)
{
    int ary1[5] = {10, 20, 30, 40, 50};
    int ary2[7] = {10, 20, 30, 40, 50, 60, 70};

    print_ary(ary1, 5);
    
    print_ary(ary2, ARY_LEN(ary2));

    return 0;
}

void print_ary(int *pa, int size)       // 같은 동작 반복하기 위해 함수 + 옆에 적히는게 선언
{
    int i;

    for (i = 0; i < size; i++) {
        printf("%d ", pa[i]);
    }
    printf("\n");       // 편의를 위해 여기로 옮김 원래 위치는 main 함수
}

//10-5.c
void print_ary(int *pa);    // 뒤에 붙이는 함수를 쓰는 이유는 가독성, main을 위해서

int main(void)
{
    int ary[5] = {10, 20, 30, 40, 50};

    print_ary(ary);

    return 0;
}

void print_ary(int *pa)     // 이걸 통해 ary를 별도로 제작 안해도 메인 함수에 접근 가능
{
    int i;

    for (i = 0; i < 5; i++) {
        printf("%d ", pa[i]);
    }
}
*/