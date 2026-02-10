#include <stdio.h>

int main(void)
{
    int a, b, c;
    int res = 0;
    int max = 0;       
    //int max; 초기화를 한번 해줘야 적합한 값이 들어감

    scanf("%d %d %d", &a, &b, &c);

    if (max < a) max = a;       //혹은 여기를 max = a 로 넣고 시작
    if (max < b) max = b;
    if (max < c) max = c;

    if (a == b) {
        max = a;
        if (a == c) {
            res = 1;
        } else {
            res = 2;
        }
    } else if (a == c) {
        max = a;
        res = 2;
    } else if (b == c) {
        max = b;
        res = 2;
    } else {
        res = 3;
    }

    switch (res) {
        case 1:
            printf("%d", (10000 + max*1000));
            break;
        case 2:
            printf("%d", (1000 + max*100));
            break;
        case 3:
            printf("%d", max*100);
            break;
        default:
            break;
    }
    

    return 0;
}
/*
    if (a == b && b == c) {
        // 세 개 다 같음
        printf("%d\n", 10000 + a * 1000);
    }
    else if (a == b || a == c) {
        // a가 같은 쌍
        printf("%d\n", 1000 + a * 100);
    }
    else if (b == c) {
        // b, c가 같은 쌍
        printf("%d\n", 1000 + b * 100);
    }
    else {
        // 전부 다름
        printf("%d\n", max * 100);
    }
*/