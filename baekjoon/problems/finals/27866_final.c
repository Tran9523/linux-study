#include <stdio.h>

int main(void)
{
    char str[1001] = {0};
    int a;

    scanf("%1001s", str);
    scanf("%d", &a);

    printf("%c\n", str[a-1]);
    return 0;
}
