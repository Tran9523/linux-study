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