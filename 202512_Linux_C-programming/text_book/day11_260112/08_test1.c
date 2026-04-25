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