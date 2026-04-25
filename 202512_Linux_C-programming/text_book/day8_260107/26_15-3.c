#include <stdio.h>
//15-3.c 문자열의 주소를 받는 포인터 -> 그 포인터 출력 위해 주소 -> 주소+주소 라 **
void print_str(char **pps, int cnt);

int main(void)
{
    char *ptr_ary[] = {"eagle", "tiger", "lion", "squirrel"};   // 포인터의 주소를 보냄
    int count;

    count = sizeof(ptr_ary) / sizeof(ptr_ary[0]);
    print_str(ptr_ary, count);      // 포인터의 주소를 보냄

    return;
}

void print_str(char **pps, int cnt) // 그래서 여기서 ** 로 받음
{
    int i;

    for (i = 0; i < cnt; i++){
        printf("%s\n", pps[i]);
    }
}