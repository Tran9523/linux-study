#include <stdio.h>

int main(void)
{
    int submit[31] = {0};
    int n;

    for (int i = 0; i <28; i++) {
        scanf("%d", &n);
        submit[n] = 1;
    }

    for (int i = 1; i <= 30; i++) {
        if (submit[i] == 0) {
            printf("%d\n", i);
        }
    }
    
    return 0;
}
