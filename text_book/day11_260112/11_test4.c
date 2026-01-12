#include <stdio.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_WEEK 32

typedef struct {
    int hour, minute, second;
} Time;

typedef struct {
    long long sec;          // 비교용 환산
    Time t;
    char week[MAX_WEEK];
} Rank;

void trim_newline(char *s);     // 한줄씩 갖고올때 마지막 개행 제거(오류 및 입출력 편의)
long long to_seconds(Time t);   // 초 환산하는 함수
Time parse_time(const char *tok);
void print_time(FILE *out, Time t);
void update_top3(Rank top[3], const char *week, Time t);    //삽입 정렬로 순위 유지

int main(void) {
    FILE *fp = fopen("usage_history.txt", "r");
    if (!fp) {
        perror("fopen() failed.");
        return 1;
    }

    Rank BA_act[3] = {0}, BA_con[3] = {0};
    Rank AC_act[3] = {0}, AC_con[3] = {0};

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp)) {     //한 줄씩 읽기
        trim_newline(line);                     //개행 제거

        char buf[MAX_LINE];                     //버퍼로 넣어서 탭 바꿀때 원본 유지
        strncpy(buf, line, sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = '\0';

        char *f[8] = {0};                       //탭 기준으로 문자열 저장
        int n = 0;
        f[n++] = buf;
        for (char *p = buf; *p; p++) {
            if (*p == '\t') {
                *p = '\0';
                f[n++] = p + 1;
            }
        }

        if (n < 5) continue;                    //제목 등 이상한 줄은 거르기

        char *week = f[0];
        Time t_ba_act = parse_time(f[1]);
        Time t_ba_con = parse_time(f[2]);

        Time t_ac_act, t_ac_con;
        if (n >= 6 && f[3][0] == '\0') {        //3번째가 탭이면 스킵, 아니면 입력
            t_ac_act = parse_time(f[4]);
            t_ac_con = parse_time(f[5]);
        } else {
            t_ac_act = parse_time(f[3]);
            t_ac_con = parse_time(f[4]);
        }

        update_top3(BA_act, week, t_ba_act);    //BA_act[3] 에서 정렬
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

    FILE *outs[2] = {stdout, out};      // 출력 파일 동시에 하기 위해

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
                print_time(o, groups[g][i].t);  //배열에 접근하는 포인터
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