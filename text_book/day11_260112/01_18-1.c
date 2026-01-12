//18-1.c    파일 열기 입문
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