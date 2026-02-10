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