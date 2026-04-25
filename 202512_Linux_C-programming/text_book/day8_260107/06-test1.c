#include <stdio.h>
//strcpy, strcat, strlen, strcmp 직접 구현 - 첫 fgets만 추가 검증
//fgets 후단을 flush 처리해놔서 elss문까진 안 내려가고 처리됨
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
    } else if (m_strlen(p1) == MAX_SIZE-1) {    // 애초에 저장이 max_size로 되서 항상 참
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