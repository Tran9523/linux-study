#include <stdio.h>

// if문 아주 간단히
int main(void)
{
    int a = 30;
    int res;

    res = (a > 10) && (a < 20);
    printf("1st %d\n", res);
    res = (a < 10) || (a > 20);
    printf("2nd %d\n", res);
    res = !(a >= 30);
    printf("3rd %d\n", res);
    
    return 0;
}