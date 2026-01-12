#include <stdio.h>

//추가(배터리 로그를 이용한 특정 데이터 추출해서 새로운 txt파일에 기록)
//여태까지 했던 실습들을 하나의 프로그램으로 만들자!(종합 계산기 -> 바퀴별 속도, 배터리 사용시간, 모터토크, 센서 정규화, 오차율 계산 등등)
//malloc 사용해서 필요한 데이터만 뽑고 반납하고, 불필요한 데이터 사용이 최소화 되도록
#include <stdio.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_WEEK 32

typedef struct {
    int hour, minute, second;
} Time;

typedef struct {
    long long sec;
    Time t;
    char week[MAX_WEEK];
} Rank;

void trim_newline(char *s);
long long to_seconds(Time t);
Time parse_time(const char *tok);
void print_time(FILE *out, Time t);
void update_top3(Rank top[3], const char *week, Time t);

int main(void) {
    FILE *fp = fopen("usage_history.txt", "r");
    if (!fp) {
        perror("fopen() failed.");
        return 1;
    }

    Rank BA_act[3] = {0}, BA_con[3] = {0};
    Rank AC_act[3] = {0}, AC_con[3] = {0};

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);

        char buf[MAX_LINE];
        strncpy(buf, line, sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = '\0';

        char *f[8] = {0};
        int n = 0;
        f[n++] = buf;
        for (char *p = buf; *p; p++) {
            if (*p == '\t') {
                *p = '\0';
                f[n++] = p + 1;
            }
        }

        if (n < 5) continue;

        char *week = f[0];
        Time t_ba_act = parse_time(f[1]);
        Time t_ba_con = parse_time(f[2]);

        Time t_ac_act, t_ac_con;
        if (n >= 6 && f[3][0] == '\0') {
            t_ac_act = parse_time(f[4]);
            t_ac_con = parse_time(f[5]);
        } else {
            t_ac_act = parse_time(f[3]);
            t_ac_con = parse_time(f[4]);
        }

        update_top3(BA_act, week, t_ba_act);
        update_top3(BA_con, week, t_ba_con);
        update_top3(AC_act, week, t_ac_act);
        update_top3(AC_con, week, t_ac_con);
    }
    fclose(fp);

    FILE *out = fopen("result.txt", "w");
    if (!out) {
        perror("fopen() failed");
        return 1;
    }

    FILE *outs[2] = {stdout, out};

    for (int k = 0; k < 2; k++) {
        FILE *o = outs[k];

        fprintf(o, "===== TOP 3 Usage Result =====\n\n");

        const char *names[4] = {
            "Battery Active", "Battery Connected Standby",
            "AC Active", "AC Connected Standby"
        };
        Rank *groups[4] = {BA_act, BA_con, AC_act, AC_con};

        for (int g = 0; g < 4; g++) {
            fprintf(o, "%s TOP3:\n", names[g]);
            for (int i = 0; i < 3; i++) {
                if (groups[g][i].sec == 0) continue;
                fprintf(o, "  %d위  %s  ", i + 1, groups[g][i].week);
                print_time(o, groups[g][i].t);
                fprintf(o, "\n");
            }
            fprintf(o, "\n");
        }
    }

    fclose(out);
    return 0;
}


void trim_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

long long to_seconds(Time t) {
    return (long long)t.hour * 3600LL +
           (long long)t.minute * 60LL +
           (long long)t.second;
}

Time parse_time(const char *tok) {
    Time t = {0, 0, 0};
    if (!tok) return t;

    while (*tok == ' ' || *tok == '\t') tok++;
    if (*tok == '\0' || (tok[0] == '-' && tok[1] == '\0')) return t;

    sscanf(tok, "%d:%d:%d", &t.hour, &t.minute, &t.second);
    return t;
}

void print_time(FILE *out, Time t) {
    fprintf(out, "%d:%02d:%02d", t.hour, t.minute, t.second);
}

void update_top3(Rank top[3], const char *week, Time t) {
    long long s = to_seconds(t);
    if (s == 0) return;

    for (int i = 0; i < 3; i++) {
        if (s > top[i].sec) {
            for (int j = 2; j > i; j--) top[j] = top[j - 1];
            top[i].sec = s;
            top[i].t = t;
            strncpy(top[i].week, week, MAX_WEEK - 1);
            top[i].week[MAX_WEEK - 1] = '\0';
            break;
        }
    }
}


/*
//fast.log 테스트
//1. 핑 요청 횟수 / 2. 가장 많은 핑을 요청한 주소(ip) / 3. 시간대별 ping요청 횟수 및 가장 잦은 IP
//IPv4는 시간대 비슷 = 이 2개가 세트라 합쳐서 1핑인 셈
//뒤의 포트 넘버 떼야함( fe80:0000:0000:0000:020c:29ff:feb7:6481 까지만)
//IPv4 (192.168.160.1) 까지만
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 512
#define MAX_IP   64
#define MAX_KEEP 5

typedef struct {
    char ip[MAX_IP];
    int cnt;
} IpCount;

static void trim_newline(char *);       //줄 가져올때 마지막 개행 바꾸기
static int extract_hour(const char *line); //시간대 추출(HH 기준)
static int extract_src_token(const char *line, char *out, size_t outsz); // IP추출
static void strip_port(char *ip);   //포트 Number 제거
static void update_ip(IpCount ips[], int *etc, const char *ip); // IPv4 계산
static void sort_ips(IpCount ips[]);    //IP 정렬
static int ends_with(const char *s, const char *suf); //마지막 단어 체크

int main(void)
{
    FILE *fp = fopen("fast.log", "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[MAX_LINE];
    int ping_cnt = 0;
    int hour_cnt[24] = {0};

    IpCount ips[MAX_KEEP] = {0};
    int etc_cnt = 0;

    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (!strstr(line, "Ping!!!!!!!!!!!")) continue;

        char src[MAX_IP];
        if (!extract_src_token(line, src, sizeof(src))) continue;

        int is_v6 = strstr(line, "{IPv6-ICMP}") != NULL;
        int is_v4 = strstr(line, "{ICMP}") != NULL;

        // IPv4는 요청(:8)만 1회
        if (is_v4 && !ends_with(src, ":8")) continue;

        strip_port(src);

        ping_cnt++;

        int h = extract_hour(line);
        if (h >= 0) hour_cnt[h]++;

        update_ip(ips, &etc_cnt, src);
    }
    fclose(fp);

    sort_ips(ips);

    int best_h = -1, best_h_cnt = -1;
    for (int i = 0; i < 24; i++) {
        if (hour_cnt[i] > best_h_cnt) {
            best_h_cnt = hour_cnt[i];
            best_h = i;
        }
    }

    printf("전체 핑 요청 횟수: [%d]\n", ping_cnt);
    if (ips[0].cnt > 0)
        printf("가장 많이 요청한 주소: [%s] (%d회)\n", ips[0].ip, ips[0].cnt);
    if (best_h >= 0)
        printf("핑 요청이 가장 많은 시간대: [%02d시] (%d회)\n", best_h, best_h_cnt);

    printf("\n[IP별 요청 횟수]\n");
    for (int i = 0; i < MAX_KEEP; i++) {
        if (ips[i].cnt > 0)
            printf("%s [%d]\n", ips[i].ip, ips[i].cnt);
    }
    if (etc_cnt > 0)
        printf("ETC [%d]\n", etc_cnt);

    return 0;
}

static void trim_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

// HH 추출
static int extract_hour(const char *line) {
    if (!isdigit((unsigned char)line[11]) || !isdigit((unsigned char)line[12])) return -1;
    int h = (line[11]-'0')*10 + (line[12]-'0');
    return (h >= 0 && h <= 23) ? h : -1;
}

// src 토큰 추출 (포트 포함 상태)
static int extract_src_token(const char *line, char *out, size_t out_sz) {
    const char *brace = strrchr(line, '}');
    if (!brace) return 0;

    const char *p = brace + 1;
    while (*p == ' ') p++;

    const char *arrow = strstr(p, " ->");
    if (!arrow) return 0;

    size_t len = arrow - p;
    if (len >= out_sz) len = out_sz - 1;

    memcpy(out, p, len);
    out[len] = '\0';
    return 1;
}

// 포트 제거: 마지막 ':' 뒤가 숫자면 포트로 판단
static void strip_port(char *ip) {
    char *last_colon = strrchr(ip, ':');
    if (!last_colon) return;

    // ':' 뒤가 전부 숫자면 포트
    for (char *p = last_colon + 1; *p; p++) {
        if (!isdigit((unsigned char)*p)) return;
    }
    *last_colon = '\0';
}

// IP 카운트 업데이트
static void update_ip(IpCount ips[], int *etc, const char *ip) {
    for (int i = 0; i < MAX_KEEP; i++) {
        if (ips[i].cnt > 0 && strcmp(ips[i].ip, ip) == 0) {
            ips[i].cnt++;
            return;
        }
    }
    for (int i = 0; i < MAX_KEEP; i++) {
        if (ips[i].cnt == 0) {
            strncpy(ips[i].ip, ip, MAX_IP - 1);
            ips[i].ip[MAX_IP - 1] = '\0';
            ips[i].cnt = 1;
            return;
        }
    }
    (*etc)++;
}

// cnt 기준 내림차순 정렬
static void sort_ips(IpCount ips[]) {
    for (int i = 0; i < MAX_KEEP - 1; i++) {
        for (int j = 0; j < MAX_KEEP - 1 - i; j++) {
            if (ips[j].cnt < ips[j + 1].cnt) {
                IpCount tmp = ips[j];
                ips[j] = ips[j + 1];
                ips[j + 1] = tmp;
            }
        }
    }
}

static int ends_with(const char *s, const char *suf) {
    size_t ls = strlen(s), lf = strlen(suf);
    return (ls >= lf && strcmp(s + ls - lf, suf) == 0);
}


/*
//log에 대한 정보를 모르는 상태에서 [Error] 기준으로 계산
#include <stdio.h>
#include <string.h>

#define MSG 256

typedef struct {
    char msg[MSG];
    int cnt;
} ErrorMSG;

static void trim_newline(char *s);

int main(void)
{
    FILE *fp;

    fp = fopen("log.txt", "r");
    if (fp == NULL) {
        printf("fopen() failed.");
        return 1;
    }
    
    char line[MSG];
    int total_cnt = 0;
    ErrorMSG Er1 = { {0}, 0};
    ErrorMSG Er2 = { {0}, 0};
    ErrorMSG Er3 = { {0}, 0};
    ErrorMSG ETC = { "ETC", 0};


    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);     //혹시 모르니 마지막 개행 삭제

        const char *tag = "[ERROR] ";
        size_t taglen = strlen(tag);

        if (strncmp(line, tag, taglen) != 0) continue;
        total_cnt++;

        const char *msg = line + taglen;

        if (Er1.cnt > 0 && strcmp(msg, Er1.msg) == 0) { Er1.cnt++; continue; }
        if (Er2.cnt > 0 && strcmp(msg, Er2.msg) == 0) { Er2.cnt++; continue; }
        if (Er3.cnt > 0 && strcmp(msg, Er3.msg) == 0) { Er3.cnt++; continue; }

        if (Er1.cnt == 0) { strncpy(Er1.msg, msg, MSG - 1); Er1.msg[MSG - 1] = '\0'; Er1.cnt = 1; }
        else if (Er2.cnt == 0) { strncpy(Er2.msg, msg, MSG - 1); Er2.msg[MSG - 1] = '\0'; Er2.cnt = 1; }
        else if (Er3.cnt == 0) { strncpy(Er3.msg, msg, MSG - 1); Er3.msg[MSG - 1] = '\0'; Er3.cnt = 1; }
        else {ETC.cnt++;}
    }

    fclose(fp);

    printf("전체 오류 횟수: [%d]\n", total_cnt);
    if (Er1.cnt > 0) printf("%s: [%d]\n", Er1.msg, Er1.cnt);
    if (Er2.cnt > 0) printf("%s: [%d]\n", Er2.msg, Er2.cnt);
    if (Er3.cnt > 0) printf("%s: [%d]\n", Er3.msg, Er3.cnt);
    if (ETC.cnt > 0) printf("%s: [%d]\n", ETC.msg, ETC.cnt);

    return 0;
}

static void trim_newline(char *s)
{
    s[strcspn(s, "\n")] = '\0';
}

/*
//log.txt 를 읽고, ERROR 총 몇회 + 어떤 오류 인지(각 횟수까지)
// '문자열'로 읽고 계산하는 - 최초 방식으로는 그냥 줄 하나 읽고 log를 역으로 계산해서 카운트하기
//gpt로 보충 계속 하기 - 이렇게 하면 뭔가 문자열을 읽는 느낌이라 나아보임
#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    char str[256] = {0};
    int cnt = 0, s_error = 0, m_error = 0;

    fp = fopen("log.txt", "r");
    if (fp == NULL) {
        printf("fopen() failed.");
        return 1;
    }
    
    while (fgets(str, sizeof(str), fp)) {
        if (strstr(str, "[ERROR]")) {
            cnt++;

            if (strstr(str, "Motor")) {
                m_error++;
            } else if (strstr(str, "Sensor")) {
                s_error++;
            }
        }
    }

    printf("전체 오류 횟수: [%d]\n", cnt);
    printf("Sensor failed: [%d]\n", s_error);
    printf("Motor overload: [%d]\n", m_error);
    fclose(fp);

    return 0;
}
//첫코드는 strstr 모르는 상태에서 나오는 로그 값을 역산하면 위치별로 카운트
//while (fgets(str, sizeof(str), fp)) {
//        int i = 0;
//        while (str[i] != '\0') {
//        if (str[i] == 'E') {
//            cnt++;
//            if (str[8] == 'M') {
//                m_error++;
//            } else if (str[8] == 'S') {
//                s_error++;
//            } else {}
//            }
//        i++;
//        }
//    }

/*
//18-7.c
#include <stdio.h>
#include <string.h>

int main(void){
    FILE *fp;
    char str[20];

    fp = fopen("a.txt", "a+");
    if (fp == NULL) {
        printf("파일을 만들지 못했습니다.\n");
        return 1;
    }
    while (1) {
        printf("과일 이름: ");
        scanf("%s", str);
        if (strcmp(str, "end") == 0) {
            break;
        } else if (strcmp(str, "list") == 0) {
            fseek(fp, 0, SEEK_SET);
            while (1) {
                fgets(str, sizeof(str), fp);
                if (feof(fp)) break;
                printf("%s", str);
            }
        } else {
            fprintf(fp, "%s\n", str);
        }
    }
    fclose(fp);

    return 0;
}

/*
//18-6.c (이건 교수님이 스킵하심)
#include <stdio.h>

int main(void)
{
    FILE *fp;
    int ary[10] = {13, 10, 13, 13, 10, 26, 13, 10, 13, 10};
    int i, res;

    fp = fopen("a.txt", "wb");  // 바이너리 파일
    
    for (i = 0; i < 10; i++) {
        fputc(ary[i], fp);
    }
    fclose(fp);

    fp = fopen("a.txt", "rt");
    while (1) {
        res = fgetc(fp);
        if (res == EOF) break;
        printf("%4d", res);
    }
    fclose(fp);

    return 0;
}

/*
//18-5.c    사용하는 함수만 getchar 에서 fgetc, fputc로 변경
#include <stdio.h>

int main(void)
{
    int ch;

    while (1) {
        ch = fgetc(stdin);
        if (ch == EOF) break;
        fputc(ch, stdout);
    }

    return 0;
}

/*
//18-4.c    버퍼의 개념을 다시 생각할 수 있도록 반복
#include <stdio.h>

int main(void)
{
    int ch;

    while (1) {
        ch = getchar();
        if (ch == EOF) {break ;}
        putchar(ch);
    }

    return 0;
}

/*
//18-3.c 이렇게 문자 넣는 테크닉 상당히 좋아보임
//[] 공백으로 받고, 그 값에서 널 문자를 만날때까지 while문 돌리기
//대신 이렇게 하면 첫 스타트부터 문장이 시작해서 덮어씌워지는 느낌
#include <stdio.h>

int main(void)
{
    FILE *fp;
    char str[] = "banana";      //여기서 문자를 이미 내가 넣었고
    int i;
                        // "a" 로 들어가면 마지막 커서 기준으로 입력을 해줌 (없으면 만들어줌)
    fp = fopen("b.txt", "w");   //수정이 아닌 작성이라 반복해도 그 줄만 남아있음
    if (fp == NULL) {
        printf("파일을 만들지 못했습니다.\n");
        return 1;
    }

    i = 0;
    while (str[i] != '\0') {
        fputc(str[i], fp);      //banana 끝의 널을 만날때까지 fp에다가 넣기
                                //받을 필요 없으니 get X
        i++;
    }
    fputc('\n', fp);
    fclose(fp);

    return 0;
}
/*
//18-2.c
#include <stdio.h>

int main(void)
{
    FILE *fp;
    int ch;

    fp = fopen("a.txt", "r");
    if (fp == NULL) {
        printf("파일이 열리지 않았습니다.\n");
        return 1;
    }

    while (1) {
        ch = fgetc(fp);
        if (ch == EOF) {        //End of File(-1)
            break;
        }
        putchar(ch);
    }
    fclose(fp);

    return 0;
}

/*
//18-1.c
#include <stdio.h>

int main(void)
{
    FILE *fp;   //file의 형태를 가리키는 포인터

    fp = fopen("a.txt", "r");   // 모드의 종류 Read & Write & Add
    if (fp == NULL) {
        printf("파일이 열리지 않았습니다.\n");
        return 1;
    }
    printf("파일이 열렸습니다.\n");
    fclose(fp);     //오픈했으면 닫는거까지 세트

    return 0;
}
*/