//이중 for문에서 중복을 뽑아내야 되는데, 그 과정이 틀렸음
#include <stdio.h>

int main(void)
{
    int i, x, cnt;
    int ary[10];

    for (i = 0; i < 10; i++) {
        scanf("%d", &x);
        ary[i] = x % 42;
    }

    // 그 나머지의 중복을 계산하는 느낌
    for (i = 0; i < 10; i++) {
        for (int j = i+1; j < 10; j++) {
            if (ary[i] != ary[j]) {
                cnt++;
            }
        }
    }
    printf("%d", cnt);

    return 0;
}
