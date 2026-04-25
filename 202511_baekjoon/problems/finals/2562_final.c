#include <stdio.h>

int main(void)
{
    int ary[9] = {0};
    int i;
    int max = 0, cnt = 0;
    
    for (i = 0; i < 9; i++) {
        scanf("%d", &ary[i]);
        if (max < ary[i]) {
            max = ary[i];
            cnt = i;
        }
    }
    
    printf("%d\n%d", max, cnt +1);

    return 0;
}