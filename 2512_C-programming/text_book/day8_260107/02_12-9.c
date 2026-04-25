#include <stdio.h>
#include <string.h>
//12-9.c
int main(void)
{
    char str[20] = "mango tree";

    strncpy(str, "apple-pie", 5);       // n 개 만큼

    printf("%s\n", str);

    return 0;
}