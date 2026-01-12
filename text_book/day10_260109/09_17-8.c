#include <stdio.h>

//17-8.c    구조체 배열 처리
struct address {
    char name[20];
    int age;
    char tel[20];
    char addr[80];
};
void print_list(struct address *lp);

int main(void)
{
    struct address list[5] = {
        {"홍길동", 23, "111-1111", "울릉도 독도"},
        {"이순신", 35, "222-2222", "서울 건천동"},
        {"장보고", 19, "333-3333", "완도 청해진"},
        {"유관순", 15, "444-4444", "충남 천안"},
        {"안중근", 45, "555-5555", "황해도 해주"},
    };

    print_lsit(list);       //배열명 = 주소

    return 0;
}

void print_list(struct address *lp) // lp주소로 받았기에 출력 형태가 a->a 형태
{
     for (int i = 0; i < 5; i++) {
        printf("%10s%5d%15s%20s\n", (lp+i)->name, (lp+i)->age, (lp+i)->tel, (lp+i)->addr);
    }
}