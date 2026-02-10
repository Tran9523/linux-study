//log에 대한 정보를 모르는 상태에서 [Error] 기준으로 계산
//사전에 미리 구조체 3개를 만들어서 에러 문구를 저장하고 그걸 출력(넘을 경우 etc로 대체)
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